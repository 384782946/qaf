#include "ConfigModel.h"
#include "QAFContext.h"

#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QDebug>
#include <QAction>

namespace QAF{

    QVariant ConfigItem::data(int index, int role /*= Qt::DisplayRole*/)
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole){

            switch (index)
            {
            case 0:
                return getName();
            case 1:
                return getValue();
            default:
                break;
            }
        }
        else if (role == Qt::DecorationRole){
            if (index == 0){
                if (getType() == CT_ATTR){
                    return QIcon(":/QAFCore/Resources/xml_attr.png");
                }
                else{
                    return QIcon(":/QAFCore/Resources/xml_text.png");
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
        if (index == 0 || (index == 2))
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

    ConfigItem* ConfigItem::getChildByName(const QString& name)
    {
        for (int i = 0; i < childCount(); i++)
        {
            ConfigItem* child = (ConfigItem*)this->child(i);
            if (child && child->getName() == name)
            {
                return child;
            }
        }
        return nullptr;
    }

    ConfigItem* ConfigItem::child(int pos)
    {
        return static_cast<ConfigItem*>(ModelItem::child(pos));
    }

    ///////////////////////////////////////////////////////////////////////////////////

    QString ConfigIterator::getPath()
    {
        Q_ASSERT(ptr);
        return ptr->getPath();
    }

    QString& ConfigIterator::operator*()
    {
        Q_ASSERT(ptr);
        return ptr->mValue;
    }

    ConfigIterator& ConfigIterator::move(int step)
    {
        if (ptr == nullptr)
            return *this;

        ModelItem* parentItem = ptr->parent();
        if (parentItem == nullptr)
            return *this;

        int index = parentItem->indexOf(ptr);
        index += step;

        if (index < step || index >= parentItem->childCount())
        {
            return *this;
        }
        else
        {
            ConfigItem* curItem = static_cast<ConfigItem*>(parentItem->child(index));
            return *this;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////

    ConfigModel::ConfigModel(QObject *parent)
        : QtCommonModel(parent),
        mIsModified(false)
    {

    }

    ConfigModel::~ConfigModel()
    {
        if (mIsModified){
            saveConfig();
        }
    }

    ConfigModel* ConfigModel::loadConfig(const QString& path)
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return nullptr;

        ConfigModel* model = new ConfigModel();
        model->mConfigFilePath = path;
        QDomDocument doc;
        if (!doc.setContent(&file))
            return nullptr;

        file.close();

        //???????xml
        typedef QPair<QDomElement, ConfigItem*> NodeType;
        QList<NodeType> tmpList;

        QDomElement root = doc.documentElement();
        tmpList.append(NodeType(root, nullptr));

        while (tmpList.size() > 0)
        {
            NodeType node = tmpList.takeLast();
            QDomElement elm = node.first;

            if (elm.isNull()||!elm.isElement())
                continue;

            ConfigItem* configItem = new ConfigItem();
            if (configItem)
            {
                configItem->setType(CT_NODE);
                configItem->setName(elm.tagName());
                if (node.second){
                    configItem->setPath(node.second->getPath() + "/" + configItem->getName());
                    model->addItem(configItem, node.second);
                }
                else{
                    configItem->setPath(configItem->getName());
                    model->addItem(configItem);
                }

                //????????
                QDomNamedNodeMap attrNodes = elm.attributes();
                for (int i = 0; i < attrNodes.count(); ++i){
                    QDomAttr attr = attrNodes.item(i).toAttr();
                    if (!attr.isNull()){
                        QString attrName = attr.name();
                        QString attrValue = attr.value();
                        ConfigItem* attrItem = new ConfigItem();
                        attrItem->setType(CT_ATTR);
                        attrItem->setName(attrName);
                        attrItem->setValue(attrValue);
                        attrItem->setPath(configItem->getPath() + "<" + attrName + ">");
                        model->addItem(attrItem, configItem);
                    }
                }

                //????????
                for (QDomNode child = elm.lastChild(); !child.isNull(); child = child.previousSibling())
                {
                    if (child.isText()){
                        QDomText t = child.toText();
                        if (!t.isNull())
                            configItem->setValue(t.data());
                    }else if (child.isElement()){
                        tmpList.append(NodeType(child.toElement(), configItem));
                    }
                }
            }
        }

        return model;
    }

    bool ConfigModel::saveConfig()
    {
        QFile file(mConfigFilePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return false;

        QDomDocument doc;
        QDomProcessingInstruction pi
            = doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\"");
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
                QDomText domText = doc.createTextNode(item->getValue());
                elm.appendChild(domText);

                for (int i = item->childCount() - 1; i >= 0; --i)
                {
                    ConfigItem* child = (ConfigItem*)item->child(i);
                    if (child->getType() == CT_ATTR){
                        elm.setAttribute(child->getName(), child->getValue());
                    }else{
                        tmpList.append(NodeType(elm, (ConfigItem*)item->child(i)));
                    }
                }

                if (node.first.isElement())
                    node.first.appendChild(elm);
                else
                    doc.appendChild(elm);
            }
        }

        QTextStream out(&file);
        out.setCodec("UTF-8");
        doc.save(out, 4, QDomNode::EncodingFromTextStream);
        file.close();

        return true;
    }

    ConfigItem* ConfigModel::query(const QString path) const
    {
        int numOfTag = path.count("<");
        Q_ASSERT_X(numOfTag <= 1, "config query", "error syntax:only one attribute is allowed in path.");

        QStringList keys = path.trimmed().split('/');
        if (keys.size() == 0)
            return nullptr;

        QString attrKey;
        if (numOfTag == 1){
            int lastIndex = keys.size() - 1;
            QString tmp = keys[lastIndex];
            int index = tmp.indexOf("<");
            keys[lastIndex] = tmp.left(index);
            attrKey = tmp.mid(index + 1, tmp.length() - index - 2);
        }

        ModelItem* item = getRootItem();
        for (int i = 0; i < keys.size();++i)
        {
            QString key = keys.at(i);
            bool match = false;

            for (int i = 0; i < item->childCount(); i++)
            {
                ConfigItem* child = (ConfigItem*)item->child(i);
                if (child && child->getName() == key)
                {
                    item = child;
                    match = true;
                    break;
                }
            }

            if (!match)
                return nullptr;
        }

        if (!attrKey.isEmpty()){
            for (int i = 0; i < item->childCount(); i++)
            {
                ConfigItem* child = (ConfigItem*)item->child(i);
                if (child && child->getType() == CT_ATTR
                    && child->getName() == attrKey)
                {
                    item = child;
                    break;
                }
            }
        }

        return (ConfigItem*)item;
    }

    QString ConfigModel::getValue(const QString& path) const
    {
        const ConfigItem* item = query(path);
        if (item)
            return item->getValue();
        else
            return "";
    }

    bool ConfigModel::isExist(const QString& path) const
    {
        return query(path) != nullptr;
    }

    bool ConfigModel::setConfigValue(const QString& path, const QString& value)
    {
        ConfigItem* item = query(path);
        if (item){
            update(item);
            return true;
        }
        return false;
    }

    void ConfigModel::update(ConfigItem* item)
    {
        if (item){
            QString path = item->getPath();
            mIsModified = true;
            emit valueChanged(path);
        }
    }

    /*ConfigIterator ConfigModel::getChild(const QString& parent_path)
    {
    ConfigItem* parentItem = query(parent_path);
    if (parent_path == nullptr)
    return ConfigIterator();

    if (parentItem->childCount() <= 0)
    return ConfigIterator();

    ConfigItem* firstItem = static_cast<ConfigItem*>(parentItem->child(0));
    return ConfigIterator(firstItem);
    }*/

    ConfigItem* ConfigModel::getItem(const QString& path)
    {
        if (path.isEmpty())
            return nullptr;

        return query(path);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////

    bool ConfigProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
    {
        if (!source_parent.isValid())
            return true;

        if (!filterRegExp().isValid() || filterRegExp().isEmpty())
            return true;

        bool filter = true;
        QModelIndex source_index = sourceModel()->index(source_row, 0, source_parent);
        ModelItem* item = static_cast<ModelItem*>(source_index.internalPointer());
        filter = QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
        if (filter)
            return true;

        for (int k = 0; k < sourceModel()->rowCount(source_index); k++)
        {
            if (filterAcceptsRow(k, source_index))
            {
                return true;
            }
        }

        return false;
    }

}
