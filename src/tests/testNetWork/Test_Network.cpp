#include "Test_Network.h"

#include "UDPServer.h"
#include "UDPClient.h"
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
}

void Test_Network::initTestCase()
{
	mUdpServer = new UDPServer(5000);

	ObjectFactory::registerClass<Request>();
	ObjectFactory::registerClass<Response>();

	mUdpServer->start();
	QThread::usleep(1000);
}

void Test_Network::cleanupTestCase()
{
	QThread::usleep(1000);
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

QTEST_MAIN(Test_Network)