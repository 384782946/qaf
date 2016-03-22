#include "ConfigSystem.h"
#include "qafcore.h"
#include "QAFDirs.h"
#include "UIInterface.h"
#include "ObjectSystem.h"
#include "ConfigModel.h"

#include <QDebug>
#include <QAction>

namespace QAF
{

	ConfigSystem::ConfigSystem(int sysId,QObject* parent)
		:AbstractSystem(sysId,parent)
	{
	}

	ConfigSystem::~ConfigSystem()
	{
		
	}

	void ConfigSystem::install()
	{
		AbstractSystem::install();

		mConfigModel = new ConfigModel(this);
		//转发信号
		connect(mConfigModel, SIGNAL(valueChanged(QString)), this, SIGNAL(configValueChanged(QString)));
		mConfigModel->setHeaders(QStringList() << LStr("名称") << LStr("状态") << LStr("值"));
		mConfigModel->loadConfig();
	}

	void ConfigSystem::uninstall()
	{
		AbstractSystem::uninstall();

		if (mIsDirty)
		{
			mConfigModel->saveConfig();
		}
	}

	bool ConfigSystem::isExist(const QString& path) const
	{
		return !path.isEmpty() && mConfigModel->isExist(path);
	}

	QString ConfigSystem::configValue(const QString& path) const
	{
		if (path.isEmpty())
			return "";

		return mConfigModel->configValue(path);
	}

	void ConfigSystem::setDirty(bool dirty)
	{
		mIsDirty = dirty;
	}

	bool ConfigSystem::isDirty() const
	{
		return mIsDirty;
	}

	bool ConfigSystem::isGroup(const QString& path) const
	{
		return mConfigModel->isGroup(path);
	}

	int ConfigSystem::groupCount(const QString& path) const
	{
		return mConfigModel->groupCount(path);
	}

	QString ConfigSystem::groupItemValue(const QString& path, int index) const
	{
		return mConfigModel->groupItemValue(path, index);
	}

}