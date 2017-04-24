#include "QAFContext.h"

#include <QCoreApplication>
#include <QDir>

#include "QAFCore.h"
#include "QAFContext.h"

namespace QAF
{
	void QAFContext::setUIInterface(UIInterface* ui)
	{
		if (ui){
			QAFCore::getSingleton()->setUIInterface(ui);
		}
	}

	UIInterface* QAFContext::getUIInterface() const
	{
		return QAFCore::getSingleton()->getUIInterface();
	}

	AbstractSystem* QAFContext::getSystem(SystemType st) const
	{
		return QAFCore::getSingleton()->getSystem(st);
	}

	void QAFContext::construct()
	{
		QAFCore::getSingleton()->initialize();
	}

	void QAFContext::destruct()
	{
		QAFCore::release();
	}

	LogModel* QAFContext::getLogModel() const
	{
		return QAFCore::getSingleton()->getLogModel();
	}

	QString QAFContext::wellKnownPath(DirType dt)
	{
		static QString dirPath = QCoreApplication::applicationDirPath();
		QString ret = dirPath;
		switch (dt)
		{
		case QAF::DT_HOME://"Bin/"
			break;
		case QAF::DT_CONFIG://"Bin/../conf"
			ret += "/../conf";
			break;
		case QAF::DT_TRANSTOR://"Bin/../lang"
			ret += "/../lang";
			break;
		case QAF::DT_LOG://"Bin/../log"
			ret += "/../log";
			break;
		case QAF::DT_DATA://"Bin/../data"
			ret += "/../data";
			break;
		case QAF::DT_PLUGIN://"Bin/plugin"
			ret += "/plugin";
			break;
		default:
			break;
		}

		QDir currDir(ret);
		if (!currDir.exists())
		{
			//auto make if don't exists
			currDir.mkpath(ret);
		}
		return currDir.absolutePath();
	}
}