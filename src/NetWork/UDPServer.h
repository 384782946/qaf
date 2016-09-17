#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include <QHostAddress>

#include "network_global.h"

#include "Handler.h"

class QUdpSocket;
class Package;
class UDPServer;

class ThreadSlots:public QObject
{
	Q_OBJECT

public:
	ThreadSlots(UDPServer* server, QObject* parent = nullptr)
		:QObject(parent),mServer(server){}

public slots :
	void readPendingDatagrams();

private:
	UDPServer* mServer;
};

class NETWORK_EXPORT UDPServer : public QThread,public Handler
{
	Q_OBJECT

	friend class ThreadSlots;
public:
	UDPServer(int port,QObject *parent = nullptr);
	~UDPServer();

	void setHandler(Handler*);

protected:

	void run();

	virtual QSharedPointer<Package> doHandle(QSharedPointer<Package>);

	void handle(const QHostAddress& address,qint16 port,QByteArray& data);

private:
	QUdpSocket* mUdpSocket;
	Handler* mHandler;
	qint16 mPort;
};

#endif // UDPSERVER_H
