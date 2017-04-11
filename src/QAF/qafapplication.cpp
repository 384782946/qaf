#include "qafapplication.h"

#include <QtWidgets/QSplashScreen>
#include <QSharedMemory>
#include <QFile>
#include <QTranslator>
#include <QTimer>
#include <QTextStream>

#include <QAFContext.h>
#include <QAFContext.h>
#include <ConfigSystem.h>

#include <QtAwesome.h>
#include "mainwindow.h"

QAFApplication::QAFApplication(int & argc, char ** argv)
    :QApplication(argc,argv),
     mSplashScreen(NULL),
     mMainWindow(NULL)
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
    options.insert("color", QColor(50,205,50));
    //options.insert("anim", qVariantFromValue(new QtAwesomeAnimation(NULL, 10, 2)));
    QIcon icon = QtAwesome::getSingleton()->icon(fa::inbox, options);
	setWindowIcon(icon);
	
	//set propertys of application
	setApplicationName("QAF");
	setOrganizationName("xiaojian");
	setOrganizationDomain("xiaojian.site");
	setApplicationVersion(QAF_VERSION_STR);

	//install qss
//	QFile f(":qdarkstyle/style.qss");
//	if (!f.exists())
//	{
//		printf("Unable to set stylesheet, file not found\n");
//	}
//	else
//	{
//        f.open(QFile::ReadOnly | QFile::Text);
//        QTextStream ts(&f);
//        qApp->setStyleSheet(ts.readAll());
//	}

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
    int ret = -1;

	initialize();

    using namespace QAF;

    QString configPath = QAFContext::wellKnownPath(QAF::DT_CONFIG);
    QAFContext* qafContext = QAFContext::getSingleton();
    ConfigSystem* configSys = static_cast<ConfigSystem*>(qafContext->getSystem(QAF::ST_CONFIG));
    if(configSys){
        if(!configSys->loadConfig(configPath+"/run.xml")){

        }
    }

	QAF::QAFContext::getSingleton()->construct();

    //延迟启动,保证1秒的启动画面
    QTimer::singleShot(1000,[=](){
        mMainWindow->showMaximized();
        mSplashScreen->finish(mMainWindow);
        mSplashScreen->deleteLater();
        mSplashScreen = nullptr;
    });

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
