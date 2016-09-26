#include "PluginSystem.h"

#include <QLibrary>
#include <QDir>
#include <QDebug>

#include "QAFContext.h"
#include "AbstractPlugin.h"
#include "QAFCore.h"
#include "ConfigModel.h"
#include "ConfigSystem.h"

typedef QAF::AbstractPluginFactory* (*LoadPluginFunc)();

namespace QAF
{
	PluginSystem::PluginSystem(int sysId, QObject* parent)
		:AbstractSystem(sysId,parent)
	{
	}

	PluginSystem::~PluginSystem()
	{
		qDeleteAll(mPlugins);
	}

	QList<PluginSystem::PluginConfig> PluginSystem::getPluginsFromConfig()
	{
		QList<PluginSystem::PluginConfig> pluginConfigs;
		ConfigItem* plugins = QAFCore::getSingleton()->getConfigSystem()->getConfig("run")->getItem("config/plugins");
		for (int i = 0; i < plugins->childCount(); ++i)
		{
			PluginConfig pc;
			ConfigItem* plugin = plugins->child(i);
			ConfigItem* configs = plugin->getChildByName("configs");
			pc.mPlugin = plugin->getChildByName("lib")->getValue();

			if (configs)
			{
				for (int j = 0; j < configs->childCount(); ++j)
				{
					ConfigItem* config = configs->child(j);
					QString key = config->getChildByName("key")->getValue();
					QString value = config->getChildByName("value")->getValue();
					pc.mConfigs[key] = value;
				}
			}

			pluginConfigs.append(pc);
		}

		return pluginConfigs;
	}

	void QAF::PluginSystem::install()
	{
		if (!isInstalled())
		{
			AbstractSystem::install();

			QString pluginPath = QAFContext::wellKnownPath(DT_PLUGIN);
			QDir dir(pluginPath);
			if (dir.exists()){
				QStringList plugins = dir.entryList(QStringList() << "*.dll", QDir::Files);
				QList<PluginConfig> pluginConfigs = getPluginsFromConfig();

				foreach(PluginConfig pluginConfig, pluginConfigs){
#ifdef QT_DEBUG
					QLibrary* library = new QLibrary(pluginPath + "/" + pluginConfig.mPlugin + "d", this);
#else
					QLibrary* library = new QLibrary(pluginPath + "/" + pluginConfig.mPlugin, this);
#endif
					if (library->load()){
						LoadPluginFunc avg = reinterpret_cast<LoadPluginFunc>(library->resolve("create"));
						if (avg){
							AbstractPluginFactory* apf = avg();
							if (apf){
								mFactorys << apf;
								qDebug() << LStr("正在加载插件:") << apf->getAuthor()
									<< apf->getDesc()
									<< apf->getType()
									<< apf->getVersion();
								
								if (apf->isAutoLoad()){
									ObjectPtr<AbstractPlugin> apPtr = apf->create();
									if (apPtr.isValid() && !apPtr->isInstalled()){
										apPtr->install(pluginConfig.mConfigs);
										apPtr->setInstalled(true);
									}
								}
							}else{
								library->unload();
								library->deleteLater();
							}
						}
					}else{
						qCritical() << LStr("插件加载失败:") << pluginConfig.mPlugin;
					}
				}
			} else{
				qCritical() << LStr("未找到插件目录");
			}
		}
	}

	void QAF::PluginSystem::uninstall()
	{
		AbstractSystem::uninstall();

		foreach(AbstractPlugin* ap, mPlugins)
		{
			if (ap)
			{
				ap->uninstall();
			}
		}
	}
}