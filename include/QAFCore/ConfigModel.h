/*!
 * \file ConfigModel.h
 * \date 2016/01/16 14:32
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * 配置项模型，基于AbstractTreeModel实现
 *
 * \note
*/

#ifndef CONFIGMODEL_H
#define CONFIGMODEL_H

#include <QSortFilterProxyModel>
#include "QAFGlobal.h"
#include "ModelItem.h"
#include "AbstractTreeModel.h"
#include "qafcore_global.h"

namespace QAF
{
	class ConfigItem :public ModelItem
	{
		friend class ConfigModel;
		
	public:
		ConfigItem():mType(CT_NODE){}

		virtual QVariant data(int index, int role = Qt::DisplayRole);
		virtual bool setData(const QVariant &value, int index, int role = Qt::DisplayRole);
		virtual int itemFlags(int);

		ConfigItem* getChildByName(const QString& name);

		void setName(QString name){ mName = name; }
		QString getName() const{ return mName; }

		void setValue(QString value){ mValue = value; }
		QString getValue() const{ return mValue; }

		void setType(ConfigType type){ mType = type; }
		ConfigType getType() const{ return mType; }

		QString typeToString(ConfigType ct);
		ConfigType stringToType(QString st);

		QString getPath() const;

	protected:
		void setPath(QString path);

	private:

		ConfigType mType;
		QString mName;
		QString mValue;
		QString mPath;
	};

	class QAFCORE_EXPORT ConfigModel : public AbstractTreeModel
	{
		Q_OBJECT
	public:
		ConfigModel(QObject *parent = nullptr);
		~ConfigModel();

		static ConfigModel* loadConfig(const QString& path);

		bool saveConfig();
		bool isModified() const { return mIsModified; }
		QString getConfigPath() const{ return mConfigFilePath; }
		QString getConfigValue(const QString& path) const;
		const ConfigItem* getConfig(const QString& path) const;
		bool isExist(const QString& path) const;
		bool setConfigValue(const QString& path, const QString& value);
		void update(ConfigItem* item);

	signals:
		void valueChanged(QString path);

	protected:
		ConfigItem* query(const QString path) const;

	private:
		QString mConfigFilePath;
		bool mIsModified;
	};

	class QAFCORE_EXPORT ConfigProxyModel : public QSortFilterProxyModel
	{
	public:
		ConfigProxyModel(QObject *parent)
			:QSortFilterProxyModel(parent){}
		~ConfigProxyModel(){}

	protected:
		virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
	};
}

#endif // CONFIGMODEL_H