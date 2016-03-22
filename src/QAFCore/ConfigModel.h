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

#include "QAFGlobal.h"
#include "ModelItem.h"
#include "AbstractTreeModel.h"

class QDomElement;
class QDomDocument;

namespace QAF
{
	class ConfigItem :public ModelItem
	{
		friend class ConfigModel;
		
	public:
		ConfigItem()
			:mActive(true)
		{
		}

		virtual QVariant data(int index, int role = Qt::DisplayRole);
		virtual bool setData(const QVariant &value, int index, int role = Qt::DisplayRole);
		virtual int itemFlags(int);

		void setName(QString name){ mName = name; }
		QString getName() const{ return mName; }

		void setValue(QString value){ mValue = value; }
		QString getValue() const{ return mValue; }

		void setType(ConfigType type){ mType = type; }
		ConfigType getType() const{ return mType; }

		void setActive(bool active){ mActive = active; }
		bool getActive() const{ return mActive; }

		void setRegx(QString regx){ mRegx = regx; }
		QString getRegx() const{ return mRegx; }

		void toXml(QDomElement* elm);
		void fromXml(QDomElement* elm);

		QString typeToString(ConfigType ct);
		ConfigType stringToType(QString st);

		QString getPath() const;

	protected:
		void setPath(QString path);

	private:
		bool mActive;
		ConfigType mType;
		QString mName;
		QString mRegx;
		QString mValue;
		QString mPath;
	};

	class ConfigModel : public AbstractTreeModel
	{
		Q_OBJECT
	public:
		ConfigModel(QObject *parent);
		~ConfigModel();

		void loadConfig();
		void saveConfig();

		QString configValue(const QString& path) const;
		bool isExist(const QString& path) const;
		bool isGroup(const QString& path) const;
		int groupCount(const QString& path) const;
		QString groupItemValue(const QString& path, int idnex) const;

	signals:
		void valueChanged(QString path);

	protected:
		ConfigItem* query(const QString path) const;

	private:

	};
}

#endif // CONFIGMODEL_H