#include "stdafx.h"
#include "qafapplication.h"

int main(int argc, char *argv[])
{
#ifdef SINGLETON_APPLICATION
	QSharedMemory shared_memory;
	shared_memory.setKey(QString("account"));

	if (shared_memory.attach())
	{
		QMessageBox::information(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��������������"), 0);
		return 1;
	}

	if (!shared_memory.create(1))
	{
		return 1;
	}
#endif

	QAFApplication app(argc, argv);
	return app.run();
}
