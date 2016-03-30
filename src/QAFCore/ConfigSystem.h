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

#pragma once

#include "AbstractSystem.h"

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
		
		void setDirty(bool dirty);
		bool isDirty() const;
		inline ConfigModel* getModel() const { return mConfigModel; }

		//model查询
		bool isExist(const QString& path) const;
		bool isGroup(const QString& path) const;
		int groupCount(const QString& path) const;
		QString groupItemValue(const QString& path, int index) const;
		QString configValue(const QString& path) const;

	signals:
		void configValueChanged(QString path);

	protected:
		
	private:
		ConfigModel* mConfigModel = nullptr;
		bool mIsDirty = false;
	};
}