#include "stdafx.h"
#include "qafapplication.h"
#include <QtWidgets/QSplashScreen>
#include <QTranslator>

#include "qafcore.h"
#include "QAFDirs.h"
#include "mainwindow.h"

using QAF::QAFDirs;

QAFApplication::QAFApplication(int & argc, char ** argv)
	:QApplication(argc,argv)
{
	
}

QAFApplication::~QAFApplication()
{

}

void QAFApplication::splashMessage(const QString& msg)
{
	QAFApplication* app = static_cast<QAFApplication*>(instance());
	if (app)
	{
		app->mSplashScreen->showMessage(msg, Qt::AlignRight | Qt::AlignBottom, Qt::white);
		processEvents();
	}	
}

void QAFApplication::initialize()
{
	//set propertys of application
	setApplicationName("QAF");
	setOrganizationName("shawkin");
	setOrganizationDomain("shawkin.com");
	setApplicationVersion(QAF_VERSION_STR);

	//install qss
	QFile f(":qdarkstyle/style.qss");
	if (!f.exists())
	{
		printf("Unable to set stylesheet, file not found\n");
	}
	else
	{
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		qApp->setStyleSheet(ts.readAll());
	}

	//install translator
	QString lang = QLocale::system().name().section('_', 0, 0);
	QString trPath = QAFDirs::path(QAF::DT_TRANSTOR);
	QString trName = "qaf_" + lang;
	QTranslator tr;
	if (tr.load(trName, trPath))
	{
		installTranslator(&tr);
	}

	//initialize splash window
	QPixmap pixmap(":/QAF/Resources/startup.png");
	mSplashScreen = new QSplashScreen(pixmap);
	mSplashScreen->show();
	processEvents();

	mMainWindow = new MainWindow();
	QAFCorePtr->initialize(QAFApplication::splashMessage);
}

int QAFApplication::run()
{
	initialize();

	int ret = 0;
	mMainWindow->showMaximized();
	mSplashScreen->finish(mMainWindow);
	mSplashScreen->deleteLater();
	ret = exec();
	mMainWindow->deleteLater();
	QAFCorePtr->release();
	return ret;
}