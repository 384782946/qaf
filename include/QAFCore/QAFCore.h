#ifndef QAFCORE_H
#define QAFCORE_H

#include <Singleton.h>
#include "QAFGlobal.h"

#include <QMap>
#include <QObject>

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

	//开机启动界面的消息回调
	typedef void(*MessageCallback)(const QString&);

	class QAFCore:public QObject,public Singleton<QAFCore>
	{
		Q_OBJECT

	public:
		QAFCore();
		~QAFCore();

		void initialize(MessageCallback fun = nullptr);

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
		MessageCallback mMessageCallback;
		UIInterface* mUIInterface;
		LogModel* mLogModel;
		bool mIsInit = false;
	};
}

#endif // QAFCORE_H