#include "PluginSystem.h"
#include "QAFDirs.h"
#include "AbstractPlugin.h"
#include "QAFCore.h"

#include <QLibrary>
#include <QDir>
#include <QDebug>

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

	void QAF::PluginSystem::install()
	{
		if (!isInstalled())
		{
			AbstractSystem::install();

			QString pluginPath = QAFDirs::path(DT_PLUGIN);
			QDir dir(pluginPath);
			if (dir.exists()){
				QStringList plugins = dir.entryList(QStringList() << "*.dll", QDir::Files);
				foreach(QString plugin, plugins){
					QLibrary* library = new QLibrary(pluginPath + "/" + plugin, this);
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
									ObjectPtr<AbstractPlugin> apPtr = apf->create(QAFCorePtr);
									if (apPtr.isValid()){
										apPtr->install();
									}
								}
							}else{
								library->unload();
								library->deleteLater();
							}
						}
					}
				}
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