#include "UDPServer.h"

#include <QtNetwork/QUdpSocket>

#include "BaseException.h"

#include "Package.h"
#include "Protocol.h"

UDPServer::UDPServer(int port,QObject *parent)
	: QThread(parent)
	, mUdpSocket(nullptr)
	, mPort(port)
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

void UDPServer::handle(const QHostAddress& address, qint16 port, QByteArray& data)
{
	QDataStream stream(&data, QIODevice::ReadOnly);
	stream.setVersion(QDataStream::Qt_5_6);

	QByteArray className;
	stream >> className;

	QSharedPointer<Package> package = ObjectFactory::createObject(className);
	if (package.isNull())
		return;

	package->unpack(stream);
	mHandler->doHandle(package);
}

QSharedPointer<Package> UDPServer::doHandle(QSharedPointer<Package> package)
{
	QSharedPointer<Request> request = qSharedPointerCast<Request>(package);
	if (request->reqestType() == RT_HEAD)
	{

	}
	else if (request->reqestType() == RT_POST)
	{
		Response* ret = new Response();
		ret->setReqestId(request->reqestId());
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

void UDPServer::run()
{
	mUdpSocket = new QUdpSocket();

	if (!mUdpSocket->bind(QHostAddress::Any, mPort, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint))
	{
		EXCEPTION_SIMPLE_THROW(QLogicException, "connot bind udpsocket!");
	}

	ThreadSlots* ts = new ThreadSlots(this);

	qDebug() << "Connect state:" << connect(mUdpSocket, SIGNAL(readyRead())
		, ts, SLOT(readPendingDatagrams()));

	exec();

	mUdpSocket->deleteLater();
	mUdpSocket = nullptr;
	ts->deleteLater();
}

//////////////////////////////////////////////////////////////////////////

void ThreadSlots::readPendingDatagrams()
{
	while (mServer->mUdpSocket->hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(mServer->mUdpSocket->pendingDatagramSize());
		QHostAddress sender;
		quint16 senderPort;

		mServer->mUdpSocket->readDatagram(datagram.data(), datagram.size(),
			&sender, &senderPort);

		mServer->handle(sender, senderPort, datagram);
	}
}
