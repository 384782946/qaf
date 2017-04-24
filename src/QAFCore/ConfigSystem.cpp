#include "ConfigSystem.h"
#include "QAFCore.h"
#include "QAFContext.h"
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
	}

	void ConfigSystem::uninstall()
	{
		AbstractSystem::uninstall();
	}

	bool ConfigSystem::isExist(const QString& confName , const QString& path) const
	{
		ConfigModel* cm = getConfig(confName);
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

		ConfigModel* cm = getConfig(confName);
		if (cm){
			return cm->getValue(path);
		}else{
			return "";
		}
	}

	bool ConfigSystem::setConfigValue(const QString& confName, const QString& path, const QString& value)
	{
		if (confName.isEmpty() || path.isEmpty())
			return "";

		ConfigModel* cm = getConfig(confName);
		if (cm){
			return cm->setConfigValue(path,value);
		}else{
			return "";
		}
	}

	ConfigModel* ConfigSystem::getConfig(const QString& key) const
	{
		return mModels.value(key,nullptr);
	}

	bool ConfigSystem::loadConfig(const QString& path)
	{
        qDebug()<<"ConfigSystem::loadConfig"<<path;
		QFileInfo fInfo(path);
		if (!fInfo.exists())
			return false;

		ConfigModel* cm = ConfigModel::loadConfig(path);
		if (cm){
			connect(cm, SIGNAL(valueChanged(QString)), this, SIGNAL(configValueChanged(QString)));
			cm->setHeaders(QStringList() << LStr("名称") << LStr("值"));
			QString key = fInfo.baseName();
			mModels.insert(key, cm);
			return true;
		}
		
		return false;
	}
}
