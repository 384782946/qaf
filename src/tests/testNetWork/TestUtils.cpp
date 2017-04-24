#include "TestUtils.h"

#include "BaseException.h"

TestUtils::TestUtils(QObject *parent)
	: QObject(parent)
{

}

TestUtils::~TestUtils()
{

}

void TestUtils::initTestCase()
{
	
}

void TestUtils::cleanupTestCase()
{

}

void TestUtils::init()
{

}

void TestUtils::cleanup()
{
	
}

void TestUtils::testException()
{
	try{
		int index = -2;
		EXCEPTION_SIMPLE_THROW(QLogicException, "test exception")(index);
	}
	catch (std::exception& e)
	{
		qDebug() << e.what();
	}
}

//QTEST_MAIN(TestUtils)
