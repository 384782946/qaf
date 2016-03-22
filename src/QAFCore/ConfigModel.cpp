#include "ConfigModel.h"
#include "QAFDirs.h"

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QDebug>
#include <QAction>

namespace QAF{

	void ConfigItem::toXml(QDomElement* childElm)
	{
		if (!childElm)
			return;

		childElm->setAttribute("type", typeToString(mType));
		childElm->setAttribute("active", mActive ? "true" : "false");

		if (mType == CT_ITEM)
		{
			childElm->setAttribute("regx", mRegx);
			childElm->setAttribute("value", mValue);
		}
	}

	void ConfigItem::fromXml(QDomElement* elm)
	{
		if (!elm)
			return;

		mName = elm->tagName().trimmed();
		mType = stringToType(elm->attribute("type").trimmed());
		setActive(elm->attribute("active").trimmed() == "true");
		
		if (mType == CT_ITEM)
		{
			mRegx = elm->attribute("regx").trimmed();
			mValue = elm->attribute("value").trimmed();
		}
	}

	QString ConfigItem::typeToString(ConfigType ct)
	{
		switch (ct)
		{
		case QAF::CT_GROUP:
			return "group";
		case QAF::CT_ITEM:
			return "item";
		default:
			break;
		}

		return QString();
	}

	ConfigType ConfigItem::stringToType(QString st)
	{
		if (st == "group")
			return CT_GROUP;
		else if (st == "item")
			return CT_ITEM;
		else
			return CT_GROUP;
	}

	QVariant ConfigItem::data(int index, int role /*= Qt::DisplayRole*/)
	{
		if (role == Qt::DisplayRole || role == Qt::EditRole){
			
			switch (index)
			{
			case 0:
				return getName();
			case 1:
				return getActive();
			case 2:
				return getValue();
			default:
				break;
			}
		}
		else if (role == Qt::DecorationRole){
			if (index == 0){
				if (getType() == CT_GROUP){
					return QIcon(":/QAFCore/Resources/folder.png");
				}
				else if (getType() == CT_ITEM){
					return QIcon(":/QAFCore/Resources/gear.png");
				}
			}
		}
		else if (role == Qt::CheckStateRole){
			return QVariant();
		}
		else if (role == Qt::StatusTipRole){
			return getPath();
		}
		
		return ModelItem::data(index, role);
	}

	bool ConfigItem::setData(const QVariant &value, int index, int role /*= Qt::DisplayRole*/)
	{
		if (role == Qt::EditRole){
			switch (index)
			{
			case 1:
				if (value.toBool() != getActive())
				{
					setActive(value.toBool());
				}
				break;
			case 2:
				if (value.toString() != getValue()){
					setValue(value.toString());
				}
				break;
			default:
				break;
			}
		}
		return ModelItem::setData(value, index, role);
	}

	int ConfigItem::itemFlags(int index)
	{
		if(index == 0 || (index == 2 && getType() == CT_GROUP))
			return Qt::ItemIsEnabled |
			Qt::ItemIsSelectable |
			Qt::ItemIsTristate;
		else
			return ModelItem::itemFlags(index);
	}

	QString ConfigItem::getPath() const
	{
		return mPath;
	}

	void ConfigItem::setPath(QString path)
	{
		mPath = path;
	}

	//////////////////////////////////////////////////////////////////////////

	ConfigModel::ConfigModel(QObject *parent)
		: AbstractTreeModel(parent)
	{

	}

	ConfigModel::~ConfigModel()
	{

	}

	void ConfigModel::loadConfig()
	{
		QString confDir = QAFDirs::path(DT_CONFIG) + "/run.xml";
		QFile file(confDir);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return;

		QDomDocument doc;
		if (!doc.setContent(&file))
			return;

		file.close();
		typedef QPair<QDomElement, ConfigItem*> NodeType;
		QList<NodeType> tmpList;

		QDomElement root = doc.documentElement();
		tmpList.append(NodeType(root, NULL));

		while (tmpList.size() > 0)
		{
			NodeType node = tmpList.takeLast();
			QDomElement elm = node.first;

			ConfigItem* configItem = new ConfigItem();
			if (configItem)
			{
				configItem->fromXml(&elm);
				if (node.second){
					node.second->addChild(configItem);
					configItem->setPath(node.second->getPath() + "/" + configItem->getName());
				}else{
					addItem(configItem);
					configItem->setPath(configItem->getName());
				}

				if (elm.isElement() && elm.hasChildNodes())
				{
					QDomElement child = elm.lastChildElement();
					for (; !child.isNull(); child = child.previousSiblingElement())
					{
						tmpList.append(NodeType(child, configItem));
					}
				}
			}
		}
	}

	void ConfigModel::saveConfig()
	{
		QDomDocument doc;
		QDomProcessingInstruction pi = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
		doc.appendChild(pi);

		typedef QPair<QDomElement, ConfigItem*> NodeType;
		QList<NodeType> tmpList;

		ConfigItem* parentItem = (ConfigItem*)itemForIndex(index(0, 0));
		tmpList.append(NodeType(QDomElement(), parentItem));
		while (tmpList.size() > 0)
		{
			NodeType node = tmpList.takeLast();
			ConfigItem* item = node.second;
			if (item)
			{
				QDomElement elm = doc.createElement(item->getName());
				if (node.first.isElement())
					node.first.appendChild(elm);
				else
					doc.appendChild(elm);

				item->toXml(&elm);

				for (int i = item->childCount() - 1; i >= 0; --i)
				{
					tmpList.append(NodeType(elm, (ConfigItem*)item->child(i)));
				}
			}
		}

		QString confDir = QAFDirs::path(DT_CONFIG) + "/run.xml";
		QFile file(confDir);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
			return;

		QTextStream out(&file);
		out.setCodec("UTF-8");
		doc.save(out, 4, QDomNode::EncodingFromTextStream);
		file.close();
	}

	ConfigItem* ConfigModel::query(const QString path) const
	{
		QStringList keys = path.split('/');

		ModelItem* item = getRootItem();

		foreach(QString key, keys)
		{
			bool match = false;
			for (int i = 0; i < item->childCount(); i++)
			{
				ConfigItem* child = (ConfigItem*)item->child(i);
				if (child && child->getActive() && child->getName() == key)
				{
					item = child;
					match = true;
					break;
				}
			}

			if (!match)
			{
				return NULL;
			}
		}

		return (ConfigItem*)item;
	}

	QString ConfigModel::configValue(const QString& path) const
	{
		if (path.isEmpty())
			return "";

		ConfigItem* item = query(path);
		if (item && item->getType() == CT_ITEM)
		{
			return item->getValue();
		}

		return "";
	}

	bool ConfigModel::isGroup(const QString& path) const
	{
		if (path.isEmpty())
			return true;

		ConfigItem* item = query(path);
		if (item)
			return item->getType() == CT_GROUP;
		else
			return true;
	}

	int ConfigModel::groupCount(const QString& path) const
	{
		if (path.isEmpty())
			return 0;

		ConfigItem* item = query(path);
		if (item)
			return item->childCount();
		else
			return 0;
	}

	QString ConfigModel::groupItemValue(const QString& path, int index) const
	{
		if (path.isEmpty())
			return "";

		ConfigItem* item = query(path);
		if (item && item->getType() == CT_GROUP)
		{
			ConfigItem* child = (ConfigItem*)item->child(index);
			if (child)
				return child->getValue();
		}
	
		return "";
	}

	bool ConfigModel::isExist(const QString& path) const
	{
		return query(path) != NULL;
	}

}