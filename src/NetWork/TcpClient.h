#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QHostAddress>

#include "Protocol.h"
#include "network_global.h"

enum TcpClientError{
	TCE_UNSPORT_RESPONSE = -100, //不支持的响应类型
	TCE_UNPACK_ERROR, //解析响应错误
	TCE_SOCKET_ERROR = QAbstractSocket::UnknownSocketError
};

#define WAIT_TIMEOUT -101

class QTcpSocket;

class NETWORK_EXPORT TcpClient : public QObject
{
	Q_OBJECT

public:
	TcpClient(QObject *parent = nullptr);
	~TcpClient();

	bool request(const QHostAddress& address,quint16 port,Request& request);

	QSharedPointer<Response> response() const;

	int waitForDone(int millisecond = -1);

signals:
	void done();
	void error(int);

protected:
	void reset();

protected slots:
	void on_connected();
	void on_disconnected();
	void on_ready_read();
	void on_bytes_written(qint64);

private:
	QTcpSocket* mSocket;
	quint64 mTotalReadLength;
	quint64 mTotalWriteLength;
	quint64 mWriteLength;
	quint64 mReadLength;

	QByteArray mWriteBuffer;
	QByteArray mReadBuffer;

	quint8 mRequestType;
	int mError;

	QSharedPointer<Response> mResponse;
};

#endif // TCPCLIENT_H
