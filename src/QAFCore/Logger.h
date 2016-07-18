#pragma once
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