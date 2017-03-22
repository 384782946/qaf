#include "stdafx.h"
#include "qafapplication.h"

#include <QMessageBox>

//#include <log4qt/logger.h>
//#include <log4qt/basicconfigurator.h>

int main(int argc, char *argv[])
{
	QApplication::addLibraryPath("");
	QAFApplication app(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));

    //Log4Qt::BasicConfigurator::configure();
    //Log4Qt::Logger* rootLogger = Log4Qt::Logger::rootLogger();
    //rootLogger->info("test log4qt");
    //rootLogger->error("test log4qt error");

    //if (!app.onlyOne()){
    //	QMessageBox::critical(NULL, "Process has been running", "Only one instance is allowed!");
    //	return 1;
    //}

    return app.run();
}
