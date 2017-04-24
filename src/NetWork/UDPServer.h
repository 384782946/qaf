#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QThread>
#include <QSharedPointer>
#include <QHostAddress>

#include "network_global.h"

#include "Handler.h"

class QUdpSocket;
class Package;
class UDPServer;

class UDPReceiver :public QObject
{
	Q_OBJECT

public:
	UDPReceiver(UDPServer* server, QObject* parent = nullptr)
		:QObject(parent), mServer(server){}

	public slots :
		void readPendingDatagrams();

private:
	UDPServer* mServer;
};

class NETWORK_EXPORT UDPServer : public QThread,public Handler
{
	Q_OBJECT

		friend class UDPReceiver;
public:
	UDPServer(int port,QObject *parent = nullptr);
	~UDPServer();

	void setHandler(Handler*);

	quint32 requestNum() const;

protected:
	void run();

	void handle(const ReqeustContext&, QByteArray& data);

	virtual QSharedPointer<Package> doHandle(const ReqeustContext&, QSharedPointer<Package>);

private:
	QUdpSocket* mUdpSocket;
	Handler* mHandler;
	qint16 mPort;
	quint32 mRequestNum;
};

#endif // UDPSERVER_H
