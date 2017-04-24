#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "network_global.h"

#include <QHash>
#include <QThread>
#include <QHostAddress>
#include <QSharedPointer>

#include "Handler.h"
#include "network_global.h"

class QTcpServer;
class QTcpSocket;
class TCPServer;

struct ClientEntity{
	QTcpSocket* Socket;
	quint64 TotalReadLength;
	quint64 ReadLength;
	quint64 TotalWriteLength;
	quint64 WriteLength;

	QByteArray ReadBuffer;
	QByteArray WriteBuffer;

	ClientEntity(){
		reset();
	}

	void reset(){
		TotalReadLength = 0;
		ReadLength = 0;
		TotalWriteLength = 0;
		WriteLength = 0;

		ReadBuffer.clear();
		WriteBuffer.clear();
	}
};

class NETWORK_EXPORT TCPReceiver :public QObject
{
	Q_OBJECT

public:
	TCPReceiver(TCPServer* server, QObject* parent = nullptr)
		:QObject(parent), mServer(server){}

public slots :
	void new_connection();
	void on_ready_read();
	void on_bytes_written(qint64);
	void on_disconnected();
	void on_error(QAbstractSocket::SocketError);

private:
	TCPServer* mServer;
};

class NETWORK_EXPORT TCPServer : public QThread,public Handler
{
	Q_OBJECT
	friend class TCPReceiver;
public:
	TCPServer(qint16 port,QObject *parent = nullptr);
	~TCPServer();

	void setHandler(Handler*);

	quint32 requestNum() const;

protected:
	void run();

	void handle(ClientEntity* entity);

	virtual QSharedPointer<Package> doHandle(const ReqeustContext& context, QSharedPointer<Package> package);

private:
	QTcpServer* mTcpServer;
	Handler* mHandler;
	qint16 mPort;

	QHash<QTcpSocket*, ClientEntity*> mClients;
	quint32 mRequestNum;
};

#endif // TCPSERVER_H
