#ifndef PLUGINSYSTEM_H
#define PLUGINSYSTEM_H

#include "AbstractSystem.h"

#include <QList>
#include <QMap>

namespace QAF
{
	class AbstractPlugin;
	class AbstractPluginFactory;

	class PluginSystem :
		public AbstractSystem
	{
		Q_OBJECT
	public:

		struct PluginConfig
		{
			QString mPlugin;
			QMap<QString, QString> mConfigs;
		};

		PluginSystem(int sysId, QObject* parent = 0);
		~PluginSystem();

		virtual void install();
		virtual void uninstall();

	protected:
		QList<PluginConfig> getPluginsFromConfig();

	private:
		QList<AbstractPlugin*> mPlugins;
		QList<AbstractPluginFactory*> mFactorys;
	};
}

#endif //PLUGINSYSTEM_H
