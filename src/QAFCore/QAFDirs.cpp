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
		case QAF::DT_HOME://"Bin/"
			ret = homeDir.absolutePath();
			break;
		case QAF::DT_CONFIG://"Bin/../conf"
			if (homeDir.cdUp() && homeDir.cd("conf"))
				ret = homeDir.absolutePath();
			break;
		case QAF::DT_TRANSTOR://"Bin/../lang"
			if (homeDir.cdUp() && homeDir.cd("lang"))
				ret = homeDir.absolutePath();
			break;
		case QAF::DT_LOG://"Bin/../log"
			if (homeDir.cdUp() && homeDir.cd("log"))
				ret = homeDir.absolutePath();
			break;
		case QAF::DT_DATA://"Bin/../data"
			if (homeDir.cdUp() && homeDir.cd("data"))
				ret = homeDir.absolutePath();
			break;
		case QAF::DT_PLUGIN://"Bin/plugin"
			if (homeDir.cd("plugin"))
				ret = homeDir.absolutePath();
			break;
		default:
			break;
		}
		return ret;
	}
}