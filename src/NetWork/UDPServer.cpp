#include "UDPServer.h"

#include <QtNetwork/QUdpSocket>

#include "BaseException.h"

#include "Package.h"
#include "Protocol.h"

UDPServer::UDPServer(int port,QObject *parent)
	: QThread(parent)
	, mUdpSocket(nullptr)
	, mPort(port)
	, mRequestNum(0)
{
	mHandler = this;
}

UDPServer::~UDPServer()
{

}

void UDPServer::setHandler(Handler* handler)
{
	mHandler = handler;
}

void UDPServer::handle(const ReqeustContext& context , QByteArray& data)
{
	QDataStream stream(&data, QIODevice::ReadOnly);
	stream.setVersion(QDataStream::Qt_5_6);

	QByteArray className;
	stream >> className;

	QSharedPointer<Package> package = ObjectFactory::createObject(className);
	if (package.isNull())
		return;

	package->unpack(stream);
	mHandler->doHandle(context,package);
	mRequestNum++;
	qDebug() << "UDPServer:receive one package.";
}

QSharedPointer<Package> UDPServer::doHandle(const ReqeustContext& context , QSharedPointer<Package> package)
{
	return QSharedPointer<Package>();
}

void UDPServer::run()
{
	mRequestNum = 0;
	mUdpSocket = new QUdpSocket();

	if (!mUdpSocket->bind(QHostAddress::Any, mPort, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint))
	{
		mUdpSocket->deleteLater();
		EXCEPTION_SIMPLE_THROW(QRuntimeException, "connot bind udpsocket!");
	}

	UDPReceiver* ts = new UDPReceiver(this);
	connect(mUdpSocket, SIGNAL(readyRead())
		, ts, SLOT(readPendingDatagrams()));

	exec();

	mUdpSocket->deleteLater();
	mUdpSocket = nullptr;
	ts->deleteLater();
}

quint32 UDPServer::requestNum() const
{
	return mRequestNum;
}

//////////////////////////////////////////////////////////////////////////

void UDPReceiver::readPendingDatagrams()
{
	while (mServer->mUdpSocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(mServer->mUdpSocket->pendingDatagramSize());

		ReqeustContext context;

		mServer->mUdpSocket->readDatagram(datagram.data(), datagram.size(),
			&context.Address, &context.Port);

		mServer->handle(context, datagram);
	}
}
