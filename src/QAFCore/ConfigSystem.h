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
		
		ConfigModel* getModel(const QString& key) const;
		bool loadModel(const QString& path);

		bool isExist(const QString& confName , const QString& path) const;
		QString getConfigValue(const QString& confName , const QString& path) const;
		bool setConfigValue(const QString& confName, const QString& path, const QString& value);

	signals:
		void configValueChanged(QString path);

	protected:
		
	private:
		ConfigModel* mRunConfig = nullptr;
		QMap<QString, ConfigModel*> mModels;
	};
}