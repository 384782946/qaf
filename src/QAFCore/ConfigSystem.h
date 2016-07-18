/*!
 * \file ConfigSystem.h
 * \date 2016/01/16 14:32
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * ���ù���ϵͳ���������õĶ�д����ʾ�ȹ���
 *
 * \note
*/

#pragma once

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
		
		void setDirty(bool dirty);
		bool isDirty() const;
		ConfigModel* getModel(const QString& key) const;

		//model��ѯ
		bool isExist(const QString& path) const;
		QString configValue(const QString& path) const;

	signals:
		void configValueChanged(QString path);

	protected:
		
	private:
		ConfigModel* mConfigModel = nullptr;
		QMap<QString, ConfigModel*> mModels;
		bool mIsDirty = false;
	};
}