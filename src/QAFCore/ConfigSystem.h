/*!
 * \file ConfigSystem.h
 * \date 2016/01/16 14:32
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * 配置管理系统，负责配置的读写、显示等功能
 *
 * \note
*/

#ifndef CONFIGSYSTEM_H
#define CONFIGSYSTEM_H

#include "qafcore_global.h"
#include "AbstractSystem.h"
#include <QMap>

namespace QAF
{
	class ConfigModel;
	class ConfigItem;

	class QAFCORE_EXPORT ConfigSystem :
		public AbstractSystem
	{
		Q_OBJECT
	public:
		ConfigSystem(int sysId, QObject* parent = 0);
		~ConfigSystem();

		virtual void install();
		virtual void uninstall();
		
		ConfigModel* getConfig(const QString& key) const;
		bool loadConfig(const QString& path);

		bool isExist(const QString& confName , const QString& path) const;
		QString getConfigValue(const QString& confName , const QString& path) const;
		bool setConfigValue(const QString& confName, const QString& path, const QString& value);

	signals:
		void configValueChanged(QString path);

	protected:
		
	private:
		QMap<QString, ConfigModel*> mModels;
	};
}

#endif //CONFIGSYSTEM_H
