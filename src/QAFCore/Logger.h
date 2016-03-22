#pragma once
#include <QtCore/QMetaType>

namespace QAF
{
	class Logger
	{
	public:
		Logger();
		~Logger();

		static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
	};
}
