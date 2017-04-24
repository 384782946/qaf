/*!
 * \file AbstractPlugin.h
 * \date 2016/01/16
 *
 * \author zxj
 *
 * \brief 
 *
 * 所有插件的基类，为插件定义基本接口
 *
 * \note
*/
#ifndef ABSTRACTPLUGIN_H
#define ABSTRACTPLUGIN_H

#include "QAFGlobal.h"
#include "AbstractObject.h"
#include "ObjectPtr.h"

namespace QAF
{
	class AbstractPluginFactory;
	class QAFCore;

	class AbstractPlugin:public AbstractObject
	{
	public:
		AbstractPlugin(){}
		virtual ~AbstractPlugin(){}

        virtual void install(const QMap<QString,QString>& params){
            Q_UNUSED(params)
			mIsInstalled = true; 
		}

        virtual void uninstall(){
			mIsInstalled = false;
		}

		bool isInstalled(){
			return mIsInstalled;
		}

		void setInstalled(bool installed){
			mIsInstalled = installed;
		}

// 		inline PluginType getType(){
// 			return mFactory?mFactory->getType():PT_NONE;
// 		}

		void setFactory(AbstractPluginFactory* factory){
			mFactory = factory;
		}

	private:
		AbstractPluginFactory* mFactory = nullptr;
		bool mIsInstalled = false;
	};

//	class PluginContext
//	{

//	};

	class AbstractPluginFactory
	{
	public:
		virtual ObjectPtr<AbstractPlugin> create() = 0;
		virtual PluginType getType() = 0;
		virtual QString getVersion() = 0;
		virtual QString getDesc() = 0;
		virtual QString getAuthor() = 0;
		virtual bool isAutoLoad() = 0;
	};
}

#endif //ABSTRACTPLUGIN_H
