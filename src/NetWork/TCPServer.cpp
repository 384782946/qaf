#include "TCPServer.h"

#include <QTcpServer>
#include <QTcpSocket>
#include "Protocol.h"
#include "BaseException.h"

TCPServer::TCPServer(qint16 port, QObject *parent)
	: QThread(parent)
	, mHandler(nullptr)
	, mTcpServer(nullptr)
	, mPort(port)
{
	setHandler(this);
}

TCPServer::~TCPServer()
{
	qDeleteAll(mClients);
	mClients.clear();
}

void TCPServer::run()
{
	mTcpServer = new QTcpServer();
	if (!mTcpServer->listen(QHostAddress::Any, mPort))
	{
		mTcpServer->deleteLater();
		EXCEPTION_SIMPLE_THROW(QRuntimeException, "tcpserver connot listen!");
	}

	TCPReceiver* ts = new TCPReceiver(this);
	connect(mTcpServer, SIGNAL(newConnection())
		, ts, SLOT(new_connection()));

	exec();

	mTcpServer->deleteLater();
	mTcpServer = nullptr;
	ts->deleteLater();
}

void TCPServer::handle(ClientEntity* entity)
{
	if (!entity)
		return;

	ReqeustContext context;
	context.Address = entity->Socket->peerAddress();
	context.Port = entity->Socket->peerPort();

	QDataStream stream(&entity->ReadBuffer, QIODevice::ReadOnly);
	stream.setVersion(QDataStream::Qt_5_7);

	QByteArray className;
	stream >> className;

	QSharedPointer<Package> package = ObjectFactory::createObject(className);
	if (!package.isNull()){
		package->unpack(stream);

		QSharedPointer<Package> response = mHandler->doHandle(context, package);
		if (!response.isNull()){
			QByteArray data;
			QDataStream stream(&data, QIODevice::ReadWrite);
			stream.setVersion(QDataStream::Qt_5_7);

			stream << quint64(0);

			if (response->pack(stream))
			{
				stream.device()->seek(0);
				stream << (quint64)data.size();
				entity->Socket->write(data);
			}
		}else{ //ÎÞ·µ»ØÖµ
			entity->Socket->close();
		}
	}
}

QSharedPointer<Package> TCPServer::doHandle(const ReqeustContext& context, QSharedPointer<Package> package)
{
	QSharedPointer<Request> request = qSharedPointerCast<Request>(package);
	if (request->reqestType() == RT_WITHOUT_RESPONSE)
	{

	}
	else if (request->reqestType() == RT_NORMAL)
	{
		Response* ret = new Response();
		ret->setStatus(RS_OK);

		QString response = "success! your post data:";
		foreach(QString key, request->data().keys())
		{
			response += QString("	%1:%2").arg(key).arg(request->data().value(key));
		}

		qDebug() << "response:" << response;

		ret->setDatas(response.toUtf8());
		return QSharedPointer<Package>(ret);
	}

	return QSharedPointer<Package>();
}

void TCPServer::setHandler(Handler* handler)
{
	mHandler = handler;
}

//////////////////////////////////////////////////////////////////////////

void TCPReceiver::new_connection()
{
	QTcpSocket* clientSocket = mServer->mTcpServer->nextPendingConnection();

	connect(clientSocket, SIGNAL(readyRead())
		, this, SLOT(on_ready_read()));
	connect(clientSocket, SIGNAL(bytesWritten(qint64))
		, this, SLOT(on_bytes_written(qint64)));
	connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError))
		, this, SLOT(on_error(QAbstractSocket::SocketError)));
	connect(clientSocket, SIGNAL(disconnected())
		, this, SLOT(on_disconnected()));

	ClientEntity* entity = new ClientEntity();
	entity->Socket = clientSocket;
	mServer->mClients[clientSocket] = entity;
}

void TCPReceiver::on_ready_read()
{
	QTcpSocket* clientSocket = (QTcpSocket*)sender();
	ClientEntity* entity = mServer->mClients.value(clientSocket, nullptr);
	if (clientSocket && entity){
		QDataStream stream((QIODevice*)clientSocket);
		stream.setVersion(QDataStream::Qt_5_7);

		if (entity->TotalReadLength == 0 && entity->Socket->bytesAvailable() >= sizeof(quint64)){ //
			stream >> entity->TotalReadLength;
			entity->ReadLength += sizeof(quint64);
		}

		if (entity->TotalReadLength >= 0){
			entity->ReadLength += entity->Socket->bytesAvailable();
			entity->ReadBuffer.append(clientSocket->readAll());

			if (entity->ReadLength >= entity->TotalReadLength){
				mServer->handle(entity);
			}
		}
	}
}

void TCPReceiver::on_bytes_written(qint64)
{

}

void TCPReceiver::on_disconnected()
{
	QTcpSocket* clientSocket = (QTcpSocket*)sender();
	ClientEntity* entity = mServer->mClients.value(clientSocket, nullptr);
	if (clientSocket && entity){
		mServer->mClients.remove(clientSocket);
		delete entity;
		clientSocket->deleteLater();
	}
}

void TCPReceiver::on_error(QAbstractSocket::SocketError socketError)
{
	QTcpSocket* clientSocket = (QTcpSocket*)sender();
	qDebug() << "TCPServer:" << "socket error" << clientSocket->errorString();
}
