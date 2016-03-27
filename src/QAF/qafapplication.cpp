#include "stdafx.h"
#include "qafapplication.h"
#include "qafcore.h"
#include "QAFDirs.h"

#include <QTranslator>

using QAF::QAFDirs;

QAFApplication* QAFApplication::sThis = NULL;

QAFApplication::QAFApplication(int & argc, char ** argv)
	:QApplication(argc,argv)
	,mSplashScreen(NULL)
	, mSplashAlign(Qt::AlignRight | Qt::AlignBottom)
	, mSplashColor(Qt::white)
{
	sThis = this;

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

	QPixmap pixmap(":/QAF/Resources/startup.png");
	mSplashScreen = new QSplashScreen(pixmap);

	setApplicationName("QAF");
	setOrganizationName("shawkin");
	setOrganizationDomain("shawkin.com");
	setApplicationVersion("1.0.0");

	QString lang = QLocale::system().name().section('_', 0, 0);
	QTranslator translator;
	if (translator.load("qaf-" + lang,"./"))
	{
		installTranslator(&translator);
	}

	QString trPath = QAFDirs::path(QAF::DT_TRANSTOR);

	QTranslator tr;
	if (tr.load(trPath))
	{
		installTranslator(&tr);
	}

	startSplash();
}

QAFApplication::~QAFApplication()
{

}

void QAFApplication::splashMessage(const QString& msg)
{
	sThis->mSplashScreen->showMessage(msg, sThis->mSplashAlign, sThis->mSplashColor);
	processEvents();
}

void QAFApplication::setSplashAlign(int align)
{
	mSplashAlign = align;
}

void QAFApplication::setSplashColor(const QColor& color)
{
	mSplashColor = color;
}

QSplashScreen* QAFApplication::splash()
{
	return mSplashScreen;
}

void QAFApplication::startSplash()
{
	mSplashScreen->show();
	processEvents();
}

void QAFApplication::finishSplash(QWidget* widget)
{
	mSplashScreen->finish(widget);
}

void QAFApplication::initialize()
{
	QAFCorePtr->initialize(QAFApplication::splashMessage);
}