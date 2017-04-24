#ifndef QAFLOGGER_H
#define QAFLOGGER_H

#include <QtCore/QMetaType>

namespace QAF
{
	class Logger
	{
	public:
		static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
		static void backTrace(int traceNum = 255);
	};
}

#endif //QAFLOGGER_H
