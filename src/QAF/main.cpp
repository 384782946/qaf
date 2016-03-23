#include "stdafx.h"
#include "mainwindow.h"
#include "qafapplication.h"

int main(int argc, char *argv[])
{
	QAFApplication app(argc, argv);
	
	app.initialize();
	
	QSharedMemory shared_memory;
	shared_memory.setKey(QString("account"));

	if (shared_memory.attach())
	{
		QMessageBox::information(nullptr, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("ֻ�ܴ�һ��Ӧ�ó���ʵ��"), 0);
		return 0;
	}

	if (shared_memory.create(1))
	{
		MainWindow w;
		w.show();
		w.showMaximized();
		app.finishSplash(&w);
		return app.exec();
	}


	return app.exec();
}
