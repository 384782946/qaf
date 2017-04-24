#ifndef TEST_NETWORK_H
#define TEST_NETWORK_H

#include <QObject>
#include <QtTest/QTest>

class UDPServer;
class TCPServer;

class Test_Network : public QObject
{
	Q_OBJECT

public:
	Test_Network(QObject *parent = 0);
	~Test_Network();

private slots:
	void initTestCase();
	void cleanupTestCase();
	void init();
	void cleanup();

	void testUdpClient_data();
	void testUdpClient();

	void testTcpClient();

private:
	UDPServer* mUdpServer;
	TCPServer* mTcpServer;
};



//#include "moc_Test_Network.cpp"

#endif // TEST_NETWORK_H
