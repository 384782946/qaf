#include "ConfigSystem.h"
#include "qafcore.h"
#include "QAFDirs.h"
#include "UIInterface.h"
#include "ObjectSystem.h"
#include "ConfigModel.h"
#include <QFileInfo>
#include <QDebug>

namespace QAF
{

	ConfigSystem::ConfigSystem(int sysId,QObject* parent)
		:AbstractSystem(sysId,parent)
	{
	}

	ConfigSystem::~ConfigSystem()
	{
		qDeleteAll(mModels);
	}

	void ConfigSystem::install()
	{
		AbstractSystem::install();

		Q_ASSERT_X(loadModel(QAFDirs::path(DT_CONFIG) + "/run.xml"),
			"ConfigSystem::install",
			"run configuration cann't be loaded.");
	}

	void ConfigSystem::uninstall()
	{
		AbstractSystem::uninstall();
	}

	bool ConfigSystem::isExist(const QString& confName , const QString& path) const
	{
		ConfigModel* cm = getModel(confName);
		if (cm){
			return !path.isEmpty() && cm->isExist(path);
		}else{
			return false;
		}
	}

	QString ConfigSystem::getConfigValue(const QString& confName,const QString& path) const
	{
		if (confName.isEmpty() || path.isEmpty())
			return "";

		ConfigModel* cm = getModel(confName);
		if (cm){
			return cm->getConfigValue(path);
		}else{
			return "";
		}
	}

	bool ConfigSystem::setConfigValue(const QString& confName, const QString& path, const QString& value)
	{
		if (confName.isEmpty() || path.isEmpty())
			return "";

		ConfigModel* cm = getModel(confName);
		if (cm){
			return cm->setConfigValue(path,value);
		}else{
			return "";
		}
	}

	ConfigModel* ConfigSystem::getModel(const QString& key) const
	{
		return mModels.value(key,nullptr);
	}

	bool ConfigSystem::loadModel(const QString& path)
	{
		QFileInfo fInfo(path);
		if (!fInfo.exists())
			return false;

		ConfigModel* cm = ConfigModel::loadConfig(path);
		if (cm){
			connect(cm, SIGNAL(valueChanged(QString)), this, SIGNAL(configValueChanged(QString)));
			cm->setHeaders(QStringList() << LStr("Ãû³Æ") << LStr("Öµ"));
			QString key = fInfo.baseName();
			mModels.insert(key, mRunConfig);
			return true;
		}
		
		return false;
	}

}