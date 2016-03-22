#include "Logger.h"

#include <QDir>
#include <stdio.h>
#include <stdlib.h>
#include "LogModel.h"
#include "QAFCore.h"
#include <QtCore/QTime>
#include <QMutex>
#include <QMutexLocker>
#include <QFile>
#include <QTextStream>

static QMutex gMutex;

namespace QAF
{
	Logger::Logger()
	{
	}


	Logger::~Logger()
	{
	}

	void Logger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
	{
		#pragma message("Note:you should define WITHOUT_LOG to disable log.")
		#ifdef WITHOUT_LOG
			return;
		#endif
		//#ifndef QT_DEBUG //release下不输出调试信息
		//	if (type == QtDebugMsg)
		//		return;
		//#endif

		QMutexLocker locker(&gMutex);
		QByteArray localMsg = msg.toLocal8Bit();
		switch (type) {
		case QtDebugMsg:
			fprintf(stdout, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtInfoMsg:
			fprintf(stdout, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtWarningMsg:
			fprintf(stdout, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtCriticalMsg:
			fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			break;
		case QtFatalMsg:
			fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
			abort();
		}

		static LogModel* logModel = nullptr;
		if (!logModel && QAFCorePtr)
		{
			logModel = QAFCorePtr->getLogModel();
		}
		
		if (logModel)
		{
			QString timeStr = QDateTime::currentDateTime().toString("yy/MM/dd hh:mm:ss");
			QAF::LogItem* item = new QAF::LogItem(type, timeStr, msg);
			logModel->addItem(item);
		}
	}
}
