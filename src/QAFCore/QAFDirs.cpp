#include "QAFDirs.h"
#include <QCoreApplication>
#include <QDir>

namespace QAF
{

	QAFDirs::QAFDirs(){}

	QAFDirs::~QAFDirs(){}

	QString QAFDirs::path(DirType type)
	{
		static QString dirPath = QCoreApplication::applicationDirPath();

		QDir homeDir(dirPath);
		QString ret = homeDir.absolutePath();
		switch (type)
		{
		case QAF::DT_HOME://"BinPath/"
			ret = homeDir.absolutePath();
			break;
		case QAF::DT_CONFIG://"BinPath/../conf"
			if (homeDir.cdUp() && homeDir.cd("conf"))
				ret = homeDir.absolutePath();
			break;
		case QAF::DT_TRANSTOR://"BinPath/../lang"
			if (homeDir.cdUp() && homeDir.cd("lang"))
				ret = homeDir.absolutePath();
			break;
		case QAF::DT_LOG://"BinPath/../log"
			if (homeDir.cdUp() && homeDir.cd("log"))
				ret = homeDir.absolutePath();
			break;
		case QAF::DT_DATA://"BinPath/../data"
			if (homeDir.cdUp() && homeDir.cd("data"))
				ret = homeDir.absolutePath();
			break;
		case QAF::DT_PLUGIN://"BinPath/../plugin"
			if (homeDir.cd("plugin"))
				ret = homeDir.absolutePath();
			break;
		default:
			break;
		}
		return ret;
	}
}