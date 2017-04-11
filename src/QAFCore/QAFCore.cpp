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
        mLogModel->setHeaders(QStringList() << LStr("类型") << LStr("时间") << LStr("内容"));

        //创建系统
        addSystem(new ObjectSystem(ST_OBJECT,this));
        addSystem(new ConfigSystem(ST_CONFIG,this));
        addSystem(new PluginSystem(ST_PLUGIN,this));
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
                removeSystem(system);
			}
		}

		//取消消息处理
		qInstallMessageHandler(0);

		mIsInit = false;
	}

	void QAFCore::initialize()
	{
		if (!mIsInit)
		{
			mIsInit = true;
			qInstallMessageHandler(Logger::messageHandler);
		
			initCore(); //初始化核心层
			initExtent(); //初始化扩展层
		}
	}

	void QAFCore::initCore()
	{
		foreach(int key, mSystems.keys()){
			if (key > ST_NONE && key < ST_CORE){
				AbstractSystem* system = mSystems.value(key, nullptr);
				if (system){
                    QString msg = QString("%1%2").arg(LStr("正在加载核心模块：")).arg(system->name());
					qDebug() << msg;
					
                    if(!system->isInstalled()){
                        system->install();
                    }
				}
			}
		}
	}

	void QAFCore::initExtent()
	{
		foreach(int key, mSystems.keys()){
			if (key > ST_CORE){
				AbstractSystem* system = mSystems.value(key, nullptr);
				if (system){
                    QString msg = QString("%1%2").arg(LStr("正在加载扩展模块：")).arg(system->name());
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
            //已丢弃，安装操作留给用户，以便用户在安装前进行一些自定义操作
            //if(!as->isInstalled()){
            //    as->install();
            //}
		}
	}

	void QAFCore::removeSystem(SystemType type)
	{
        removeSystem(getSystem(type));
    }

    void QAFCore::removeSystem(AbstractSystem * sys)
    {
        if(sys == NULL)
            return;

        int key = mSystems.key(sys,-1);
        if (key != -1 && mSystems.contains(key))
        {
            QString msg;
            if (key > ST_NONE && key < ST_CORE){
                msg = QString("%1%2").arg(LStr("正在卸载核心模块：")).arg(sys->name());
            }
            else if (key > ST_CORE){
                msg = QString("%1%2").arg(LStr("正在卸载扩展模块：")).arg(sys->name());
            }

            qDebug() << msg;

            mSystems.remove(key);
            sys->uninstall();
            sys->deleteLater();
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
