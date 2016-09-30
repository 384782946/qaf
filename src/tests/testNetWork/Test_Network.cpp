#include "Test_Network.h"

#include "UDPServer.h"
#include "UDPClient.h"
#include "TCPServer.h"
#include "TcpClient.h"
#include "Protocol.h"

Test_Network::Test_Network(QObject *parent)
	: QObject(parent)
{

}

Test_Network::~Test_Network()
{

}

void Test_Network::testUdpClient_data()
{

}

void Test_Network::testUdpClient()
{
	Request request;
	QMap<QString, QString> params;
	params["key1"] = "value1";
	params["key2"] = "value2";
	request.setData(params);
	UDPClient::send(request, QHostAddress::LocalHost, 5000);
	QThread::usleep(100);
	QVERIFY(mUdpServer->requestNum() == 1);
}

void Test_Network::initTestCase()
{
	mUdpServer = new UDPServer(5000);
	mTcpServer = new TCPServer(5001);

	ObjectFactory::registerClass<Request>();
	ObjectFactory::registerClass<Response>();

	mUdpServer->start();
	mTcpServer->start();
	QThread::usleep(1000);
}

void Test_Network::cleanupTestCase()
{
	QThread::usleep(1000);
	mTcpServer->quit();
	mTcpServer->wait();
	mTcpServer->deleteLater();
	mUdpServer->quit();
	mUdpServer->wait();
	mUdpServer->deleteLater();
}

void Test_Network::init()
{

}

void Test_Network::cleanup()
{
	
}

void Test_Network::testTcpClient()
{
	TcpClient client;

	Request request;
	request.setReqestType(RT_NORMAL);

	QMap<QString, QString> datas;
	datas["key"] = "value";
	datas["url"] = "/index";
	request.setData(datas);

	client.request(QHostAddress::LocalHost, 5001, request);
	client.waitForDone();

	qDebug() << client.response()->datas();
}

QTEST_MAIN(Test_Network)