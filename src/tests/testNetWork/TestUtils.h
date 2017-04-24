#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QObject>
#include <QtTest/QTest>

class TestUtils : public QObject
{
	Q_OBJECT

public:
	TestUtils(QObject *parent = 0);
	~TestUtils();

private slots:
	void initTestCase();
	void cleanupTestCase();
	void init();
	void cleanup();

	void testException();
};

#endif // TESTUTILS_H
