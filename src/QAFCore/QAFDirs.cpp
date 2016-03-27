#include "QAFDirs.h"
#include <QCoreApplication>
#include <QDir>

namespace QAF
{

	QString QAFDirs::path(DirType type)
	{
		static QString dirPath = QCoreApplication::applicationDirPath();
		QString ret = dirPath;
		switch (type)
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