#include <QString>
#include <QtTest>

#include <QAFCore.h>
#include <QAFContext.h>
#include <ObjectSystem.h>
#include <AbstractObject.h>

using namespace QAF;

class TestObject:public AbstractObject{
public:
    TestObject(int index = 0):data(index){}

    int getData() const { return data; }
    void setData(int index){ data = index; }

private:
    int data;
};

class TestQAFCoreTest : public QObject
{
    Q_OBJECT

public:
    TestQAFCoreTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    //void testCase1_data();
    //void testCase1();

    void testCreateObject();
    void testCreateObjectArray();
    void testDestoryObject();
};

TestQAFCoreTest::TestQAFCoreTest()
{
}

void TestQAFCoreTest::initTestCase()
{
    QAF::QAFContext::getSingleton()->construct();
}

void TestQAFCoreTest::cleanupTestCase()
{
    QAF::QAFContext::getSingleton()->destruct();
}

//void TestQAFCoreTest::testCase1_data()
//{
//    //QTest::addColumn<QString>("data");
//    //QTest::newRow("0") << QString();
//}

void TestQAFCoreTest::testCreateObject()
{
    ObjectSystem* os = static_cast<ObjectSystem*>(QAF::QAFContext::getSingleton()->getSystem(QAF::ST_OBJECT));
    Q_ASSERT_X(os != NULL,"TestQAFCoreTest::testCase1","can not get object system");
    //QFETCH(QString, data);
    QBENCHMARK_ONCE {
        int objectCount = os->objectCount();
        for(int i = 0;i<10000;++i){
            os->create<TestObject>(i);
        }

        QVERIFY(objectCount+10000 == os->objectCount());
        //qDebug()<<"Object Count:"<<os->objectCount();
    }
}

void TestQAFCoreTest::testCreateObjectArray()
{
    ObjectSystem* os = static_cast<ObjectSystem*>(QAF::QAFContext::getSingleton()->getSystem(QAF::ST_OBJECT));
    Q_ASSERT_X(os != NULL,"TestQAFCoreTest::testCase1","can not get object system");
    //QFETCH(QString, data);
    QBENCHMARK_ONCE {
        int objectCount = os->objectCount();
        int index = 0;
        QList<QAF::ObjectPtr<TestObject>> objects = os->createArray<TestObject>(10000);
        qDebug()<<"objects size"<<objects.size();
        foreach(QAF::ObjectPtr<TestObject> object,objects){
            object->setData(index++);
        }

        QVERIFY(objectCount+10000 == os->objectCount());
        //qDebug()<<"Object Count:"<<os->objectCount();
    }
}

void TestQAFCoreTest::testDestoryObject()
{
    ObjectSystem* os = static_cast<ObjectSystem*>(QAF::QAFContext::getSingleton()->getSystem(QAF::ST_OBJECT));
    QVERIFY2(os != NULL,"can not get object system");
    //QFETCH(QString, data);
    qDebug()<<"Object Count:"<<os->objectCount();

    foreach(ObjectId id,os->objects()){
        ObjectPtr<TestObject> ptr = os->object<TestObject>(id);
        //qDebug()<<id<<ptr->getData();
        os->destory(id);
    }

    qDebug()<<"Object Count:"<<os->objectCount();
}

QTEST_APPLESS_MAIN(TestQAFCoreTest)

#include "tst_testqafcoretest.moc"
