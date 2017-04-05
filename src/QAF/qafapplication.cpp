#include "stdafx.h"
#include "qafapplication.h"
#include <QtWidgets/QSplashScreen>
#include <QTranslator>
#include <QAFContext.h>
#include <QAFContext.h>
#include <QtAwesome.h>

#include "mainwindow.h"

QAFApplication::QAFApplication(int & argc, char ** argv)
	:QApplication(argc,argv)
{
	
}

QAFApplication::~QAFApplication()
{

}

void QAFApplication::splashMessage(QString msg)
{
	QAFApplication* app = static_cast<QAFApplication*>(instance());
	if (app && app->mSplashScreen)
	{
		app->mSplashScreen->showMessage(msg, Qt::AlignRight | Qt::AlignBottom, Qt::white);
		processEvents();
	}	
}

void QAFApplication::initialize()
{

	QtAwesome::getSingleton()->initFontAwesome();
	QVariantMap options;
	//options.insert("color-active", QColor(205,0,0 ) );
	//options.insert("anim", qVariantFromValue(new QtAwesomeAnimation(beerButton, 10, 2)));
	QIcon icon = QtAwesome::getSingleton()->icon(fa::locationarrow, options);
	setWindowIcon(icon);
	
	//set propertys of application
	setApplicationName("QAF");
	setOrganizationName("xiaojian");
	setOrganizationDomain("xiaojian.site");
	setApplicationVersion(QAF_VERSION_STR);

	//install qss
	QFile f(":qdarkstyle/style.qss");
	if (!f.exists())
	{
		printf("Unable to set stylesheet, file not found\n");
	}
	else
	{
        //f.open(QFile::ReadOnly | QFile::Text);
        //QTextStream ts(&f);
        //qApp->setStyleSheet(ts.readAll());
	}

	//install translator
	QString lang = QLocale::system().name().section('_', 0, 0);
	QString trPath = QAF::QAFContext::wellKnownPath(QAF::DT_TRANSTOR);
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
}

int QAFApplication::run()
{
	initialize();

	QAF::QAFContext::getSingleton()->construct();

	int ret = 0;
	mMainWindow->showMaximized();
	mSplashScreen->finish(mMainWindow);
	mSplashScreen->deleteLater();
	mSplashScreen = nullptr;
	ret = exec();
	mMainWindow->deleteLater();
	mMainWindow = nullptr;

	QAF::QAFContext::getSingleton()->destruct();
	return ret;
}

bool QAFApplication::onlyOne()
{
	static QSharedMemory shared_memory;
	shared_memory.setKey(qApp->applicationName());

	if (shared_memory.attach()) {
		return false;
	}else{
		shared_memory.create(1);
	}
	
	return true;
}
