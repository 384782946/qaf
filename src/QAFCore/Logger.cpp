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
#include "QAFDirs.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#include "DbgHelp.h"
#pragma comment(lib, "Dbghelp.lib")
#endif

static QMutex gMutex;
static QFile* gLogFile = nullptr;
static QTextStream gLogStream;

namespace QAF
{
	void Logger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
	{
#pragma message("Note:you can define WITHOUT_LOG to disable log.")
#ifndef WITHOUT_LOG

		QMutexLocker locker(&gMutex);
		if (!gLogFile){
			QString logName = QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss")+".txt";
			QString logPath = QAFDirs::path(DT_LOG) + "/" + logName;
			gLogFile = new QFile(logPath,QAFCorePtr);
			if (gLogFile->open(QIODevice::WriteOnly)){
				gLogStream.setDevice(gLogFile);
				gLogStream.setCodec("UTF-8");
			} else{
				throw "Can not open log file.";
			}
		}

		static char msgType[][10] = { "Debug", "Warning", "Critical", "Fatal", "Info" };
		QString stamp = QString("%1\tType:%2\tFile:%3\tLine:%4\tFunction:%5\n\t")
			.arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
			.arg(msgType[type])
			.arg(context.file)
			.arg(context.line)
			.arg(context.function);

		gLogStream << stamp << msg <<"\n";
		gLogStream.flush();
		
		QByteArray localMsg = msg.toLocal8Bit();
		switch (type) {
		case QtDebugMsg:
		fprintf(stdout, "Debug: %s\n", localMsg.constData());
		break;
		case QtInfoMsg:
		fprintf(stdout, "Info: %s\n", localMsg.constData());
		break;
		case QtWarningMsg:
		fprintf(stdout, "Warning: %s\n", localMsg.constData());
		break;
		case QtCriticalMsg:
		fprintf(stderr, "Critical: %s\n", localMsg.constData());
		break;
		case QtFatalMsg:
		fprintf(stderr, "Fatal: %s\n", localMsg.constData());
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
#endif
	}

	void Logger::backTrace(int traceNum /*= 255*/)
	{
#ifdef Q_OS_WIN
		void ** stack = new void*[ traceNum ];
		HANDLE process = GetCurrentProcess();
		SymInitialize(process, nullptr, TRUE);
		unsigned short frames = CaptureStackBackTrace(0, traceNum, stack, nullptr);
		SYMBOL_INFO  * symbol = (SYMBOL_INFO *)calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
		symbol->MaxNameLen = 255;
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

		for (int i = 0; i < frames; i++)
		{
			SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);

			printf("%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address);
		}

		free(symbol);
#else
		//current os do not support back trace. 
#endif
	}
}
