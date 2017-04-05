#ifndef QAFCORE_H
#define QAFCORE_H

#include <QMap>
#include <QObject>

#include "Singleton.h"
#include "QAFGlobal.h"

class QAbstractItemModel;

namespace QAF
{
	class AbstractObject;
	class AbstractSystem;
	class PluginSystem;
	class UIInterface;
	class ConfigSystem;
	class ObjectSystem;
	class LogModel;

	class QAFCore:public QObject,public Singleton<QAFCore>
	{

	public:
		QAFCore();
		~QAFCore();

		void initialize();

		void addSystem(AbstractSystem*);
		void removeSystem(SystemType);
		AbstractSystem* getSystem(SystemType type) const;
		ConfigSystem* getConfigSystem() const;
		ObjectSystem* getObjectSystem(int sysId = ST_OBJECT) const;
		PluginSystem* getPluginSystem() const;

		void setUIInterface(UIInterface*);
		UIInterface* getUIInterface() const;
		LogModel* getLogModel() const;

		int getVersion() const;
		QString getVersionStr() const;
		bool isSupported(int version) const;

	protected:
		void initCore();
		void initExtent();
		void destory();

	private:
		QMap<int, AbstractSystem*> mSystems;
		UIInterface* mUIInterface;
		LogModel* mLogModel;
		bool mIsInit = false;
	};
}

#endif // QAFCORE_H