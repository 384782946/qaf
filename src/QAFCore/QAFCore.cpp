#include "QAFCore.h"
#include <QDockWidget>
#include <QDebug>
#include "ObjectSystem.h"
#include "PluginSystem.h"
#include "ConfigSystem.h"
#include "UIInterface.h"
#include "QAFLogger.h"
#include "LogModel.h"

namespace QAF
{
	QAFCore::QAFCore()
		:mUIInterface(nullptr)
		, mLogModel(new QAF::LogModel())
	{
		mLogModel->setHeaders(QStringList() << LStr("����") << LStr("ʱ��") << LStr("����"));
	}

	QAFCore::~QAFCore()
	{
		if (mIsInit){
			destory();
		}
	}

	void QAFCore::destory()
	{
		foreach(int key, mSystems.keys()){
			AbstractSystem* system = mSystems.value(key, nullptr);
			if (system){
				QString msg;
				if (key > ST_NONE && key < ST_CORE){
					msg = QString("%1%2").arg(LStr("����ж�غ���ģ�飺")).arg(system->name());
				}
				else if (key > ST_CORE){
					msg = QString("%1%2").arg(LStr("����ж����չģ�飺")).arg(system->name());
				}

				qDebug() << msg;
				system->uninstall();
			}
		}

		qDeleteAll(mSystems);

		//ȡ����Ϣ����
		qInstallMessageHandler(0);

		mIsInit = false;
	}

	void QAFCore::initialize()
	{
		if (!mIsInit)
		{
			mIsInit = true;
			qInstallMessageHandler(Logger::messageHandler);
		
			initCore(); //��ʼ�����Ĳ�
			initExtent(); //��ʼ����չ��
		}
	}

	void QAFCore::initCore()
	{
		addSystem(new ObjectSystem(ST_OBJECT,this));
		addSystem(new ConfigSystem(ST_CONFIG,this));

		foreach(int key, mSystems.keys()){
			if (key > ST_NONE && key < ST_CORE){
				AbstractSystem* system = mSystems.value(key, nullptr);
				if (system){
					QString msg = QString("%1%2").arg(LStr("���ڼ��غ���ģ�飺")).arg(system->name());
					qDebug() << msg;
					
					system->install();
				}
			}
		}
	}

	void QAFCore::initExtent()
	{
		addSystem(new PluginSystem(ST_PLUGIN,this));

		foreach(int key, mSystems.keys()){
			if (key > ST_CORE){
				AbstractSystem* system = mSystems.value(key, nullptr);
				if (system){
					QString msg = QString("%1%2").arg(LStr("���ڼ�����չģ�飺")).arg(system->name());
					qDebug() << msg;
					
					system->install();
				}
			}
		}
	}

	void QAFCore::addSystem(AbstractSystem* as)
	{
		if (!as)
			return;

		int id = as->systemId();
		if (!mSystems.contains(id))
		{
			mSystems.insert(id, as);
		}
	}

	void QAFCore::removeSystem(SystemType type)
	{
		if (mSystems.contains(type))
		{
			AbstractSystem* as = mSystems.take(type);
			if (as)
			{
				as->uninstall();
				delete as;
			}
		}
	}

	AbstractSystem* QAFCore::getSystem(SystemType type) const
	{
		return mSystems.value(type, nullptr);
	}

	void QAFCore::setUIInterface(UIInterface* ui)
	{
		if (ui && !mUIInterface)
			mUIInterface = ui;
	}

	UIInterface* QAFCore::getUIInterface() const
	{
		return mUIInterface;
	}

	ConfigSystem* QAFCore::getConfigSystem() const
	{
		return static_cast<ConfigSystem*>(getSystem(ST_CONFIG));
	}

    ObjectSystem* QAFCore::getObjectSystem(int) const
	{
		return static_cast<ObjectSystem*>(getSystem(ST_OBJECT));
	}

	PluginSystem* QAFCore::getPluginSystem() const
	{
		return static_cast<PluginSystem*>(getSystem(ST_PLUGIN));
	}

	LogModel* QAFCore::getLogModel() const
	{
		return mLogModel;
	}

	int QAFCore::getVersion() const
	{
		return QAF_VERSION;
	}

	QString QAFCore::getVersionStr() const
	{
		return QAF_VERSION_STR;
	}

	bool QAFCore::isSupported(int version) const
	{
		return getVersion() >= version;
	}

}
