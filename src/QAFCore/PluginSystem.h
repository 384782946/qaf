#pragma once

#include "AbstractSystem.h"

#include <QList>

namespace QAF
{
	class AbstractPlugin;
	class AbstractPluginFactory;

	class PluginSystem :
		public AbstractSystem
	{
		Q_OBJECT
	public:
		PluginSystem(int sysId, QObject* parent = 0);
		~PluginSystem();

		virtual void install();
		virtual void uninstall();

	private:
		QList<AbstractPlugin*> mPlugins;
		QList<AbstractPluginFactory*> mFactorys;
	};
}