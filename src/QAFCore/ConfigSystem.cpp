#include "ConfigSystem.h"
#include "qafcore.h"
#include "QAFDirs.h"
#include "UIInterface.h"
#include "ObjectSystem.h"
#include "ConfigModel.h"
#include <QFileInfo>
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

		ConfigModel* configModel = new ConfigModel(this);
		//转发信号
		connect(configModel, SIGNAL(valueChanged(QString)), this, SIGNAL(configValueChanged(QString)));
		configModel->setHeaders(QStringList() << LStr("名称") << LStr("值"));
		QString path = QAFDirs::path(DT_CONFIG) + "/run.xml";
		configModel->loadConfig(path);
		QFileInfo fInfo(path);
		QString key = fInfo.baseName();
		mModels.insert(key, configModel);
	}

	void ConfigSystem::uninstall()
	{
		AbstractSystem::uninstall();

		//if (mIsDirty)
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

		return mConfigModel->getConfigValue(path);
	}

	void ConfigSystem::setDirty(bool dirty)
	{
		mIsDirty = dirty;
	}

	bool ConfigSystem::isDirty() const
	{
		return mIsDirty;
	}

	ConfigModel* ConfigSystem::getModel(const QString& key) const
	{
		return mModels.value(key,nullptr);
	}

}