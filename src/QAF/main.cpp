#include "stdafx.h"
#include "mainwindow.h"
#include "qafapplication.h"

int main(int argc, char *argv[])
{
	QAFApplication app(argc, argv);
	
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

	MainWindow w;
	app.initialize();
	w.showMaximized();
	app.finishSplash(&w);
	return app.exec();
}
