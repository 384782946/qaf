#ifndef QAFCORE_H
#define QAFCORE_H

#include "QAFGlobal.h"
#include "Singleton.h"

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

	class QAFCORE_EXPORT QAFCore :public QObject,public Singleton<QAFCore>
	{
		Q_OBJECT

	public:
		QAFCore();
		~QAFCore();

		//初始化
		void initialize(MessageCallback fun = NULL);

		void addSystem(AbstractSystem*);
		void removeSystem(SystemType);
		AbstractSystem* getSystem(int type /*SystemType*/) const;
		ConfigSystem* getConfigSystem() const;
		ObjectSystem* getObjectSystem(int sysId = ST_OBJECT) const;
		PluginSystem* getPluginSystem() const;

		void setUIInterface(UIInterface*);
		UIInterface* getUIInterface() const;
		inline LogModel* getLogModel() const;

		inline int getVersion() const;
		inline QString getVersionStr() const;
		inline bool isSupported(int version) const;

	protected:
		void initCore();
		void initExtent();

	private:
		QMap<int, AbstractSystem*> mSystems;
		MessageCallback mMessageCallback;
		UIInterface* mUIInterface;
		LogModel* mLogModel;
	};
}

#endif // QAFCORE_H