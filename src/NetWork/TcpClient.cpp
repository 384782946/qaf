#include "TcpClient.h"

#include <QTcpSocket>
#include <QEventLoop>
#include <QTimer>

#include "Protocol.h"

#define MTU 1024

TcpClient::TcpClient(QObject *parent)
	: QObject(parent)
	, mError(0)
{
	mSocket = new QTcpSocket(this);

	connect(mSocket, SIGNAL(readyRead())
		, this, SLOT(on_ready_read()));
	connect(mSocket, SIGNAL(bytesWritten(qint64))
		, this, SLOT(on_bytes_written(qint64)));
	connect(mSocket, SIGNAL(connected())
		, this, SLOT(on_connected()));
	connect(mSocket, SIGNAL(disconnected())
		, this, SLOT(on_disconnected()));

	connect(mSocket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
		[=](QAbstractSocket::SocketError socketError){ 
		qDebug() << "socket error:" << mSocket->errorString(); mError = (int)socketError + 100; });
}

TcpClient::~TcpClient()
{

}

bool TcpClient::request(const QHostAddress& address, quint16 port, Request& request)
{
	if (mSocket->isOpen())
		return false;

	reset();

	mRequestType = request.reqestType();

	QDataStream stream(&mWriteBuffer, QIODevice::ReadWrite);

	stream << quint64(0);
	request.pack(stream);
	stream.device()->seek(0);
	stream << quint64(mWriteBuffer.size());

	mTotalWriteLength = mWriteBuffer.size();

	mSocket->connectToHost(address, port);
	return true;
}

void TcpClient::reset()
{
	mError = 0;

	mTotalReadLength = 0;
	mTotalWriteLength = 0;
	mWriteLength = 0;
	mReadLength = 0;

	mWriteBuffer.clear();
	mReadBuffer.clear();
	mResponse.reset();
}

void TcpClient::on_ready_read()
{
	QDataStream stream(mSocket);
	stream.setVersion(QDataStream::Qt_5_7);
	if (mTotalReadLength == 0 && mSocket->bytesAvailable() >= sizeof(quint64)){ //
		stream >> mTotalReadLength;
		mReadLength += sizeof(quint64);
	}

	if (mTotalReadLength >= 0){
		mReadLength += mSocket->bytesAvailable();
		mReadBuffer.append(mSocket->readAll());

		if (mReadLength >= mTotalReadLength){
			mSocket->disconnectFromHost();
		}
	}
}

void TcpClient::on_bytes_written(qint64 bytes)
{
	mWriteLength += bytes;
	if (mWriteLength < mTotalWriteLength){
		int len = (mTotalWriteLength - mWriteLength) > MTU ? MTU : (mTotalWriteLength - mWriteLength);
		mSocket->write(mWriteBuffer.mid(mWriteLength, len));
	}else{ //发送完毕,且无返回数据
		if(mRequestType >= RT_WITHOUT_RESPONSE)
			mSocket->disconnectFromHost();
	}
}

void TcpClient::on_connected()
{
	int len = (mTotalWriteLength - mWriteLength) > MTU ? MTU : (mTotalWriteLength - mWriteLength);
	mSocket->write(mWriteBuffer.mid(0, len));
}

void TcpClient::on_disconnected()
{
	if (mRequestType < RT_WITHOUT_RESPONSE){ //带返回的请求需要解析返回结果
		QDataStream stream(&mReadBuffer, QIODevice::ReadOnly);
		QByteArray className;
		stream >> className;
		mResponse = qSharedPointerCast<Response>(ObjectFactory::createObject(className));
		if (mResponse.isNull())
			mError = TCE_UNSPORT_RESPONSE;
		else if (!mResponse->unpack(stream))
			mError = TCE_UNPACK_ERROR;
	}
	
	if (mError != 0)
		emit error(mError<0?mError:(mError-100));
	else
		emit done();
}

QSharedPointer<Response> TcpClient::response() const
{
	return mResponse;
}

int TcpClient::waitForDone(int millisecond)
{
	QEventLoop eventLoop;
	connect(this, &TcpClient::done, &eventLoop, &QEventLoop::quit);
	connect(this, &TcpClient::error, [&eventLoop](int error){
		eventLoop.exit(error);
	});

	if (millisecond > 0){
		QTimer::singleShot(millisecond, [&eventLoop](){
			eventLoop.exit(WAIT_TIMEOUT);
		});
	}
	
	return eventLoop.exec();
}
