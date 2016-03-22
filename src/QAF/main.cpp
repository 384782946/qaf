#include "stdafx.h"
#include "mainwindow.h"
#include "qafapplication.h"

int main(int argc, char *argv[])
{
	QAFApplication app(argc, argv);
	
	MainWindow w;
	app.initialize();
	
	w.show();
	app.finishSplash(&w);
	return app.exec();
}
