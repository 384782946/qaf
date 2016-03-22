#include "QAFDirs.h"
#include <QCoreApplication>
#include <QDir>

namespace QAF
{

	QString QAFDirs::path(DirType type)
	{
		static QString dirPath = QCoreApplication::applicationDirPath();
		//QDir homeDir(dirPath);
		QString ret = dirPath;
		switch (type)
		{
		case QAF::DT_HOME://"Bin/"
			//ret = homeDir.absolutePath();
			break;
		case QAF::DT_CONFIG://"Bin/../conf"
			ret += "/../conf";
			//if (homeDir.cdUp() && homeDir.cd("conf"))
			//	ret = homeDir.absolutePath();
			break;
		case QAF::DT_TRANSTOR://"Bin/../lang"
			ret += "/../lang";
			//if (homeDir.cdUp() && homeDir.cd("lang"))
			//	ret = homeDir.absolutePath();
			break;
		case QAF::DT_LOG://"Bin/../log"
			ret += "/../log";
			//if (homeDir.cdUp() && homeDir.cd("log"))
			//	ret = homeDir.absolutePath();
			break;
		case QAF::DT_DATA://"Bin/../data"
			ret += "/../data";
			//if (homeDir.cdUp() && homeDir.cd("data"))
			//	ret = homeDir.absolutePath();
			break;
		case QAF::DT_PLUGIN://"Bin/plugin"
			//ret += "/plugin";
			//if (homeDir.cd("plugin"))
			//	ret = homeDir.absolutePath();
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