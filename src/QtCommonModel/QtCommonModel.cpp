#include "QtCommonModel.h"
#include "ModelItem.h"

QtCommonModel::QtCommonModel(QObject *parent)
	: QAbstractItemModel(parent)
    , mRootItem(new RootItem())
{

}

QtCommonModel::~QtCommonModel()
{
    mModelHash.clear();;
}

QModelIndex	QtCommonModel::parent(const QModelIndex & index) const
{
    ModelItemPtr item = itemForIndex(index);
	if (!item)
		return QModelIndex();

    ModelItemPtr parent = item->parent();
	if (!parent)
		return QModelIndex();

    ModelItemPtr grandparent = parent->parent();
	if (!grandparent)
		return QModelIndex();

	int row = grandparent->indexOf(parent);
    return createIndex(row, 0, parent);
}

int QtCommonModel::rowCount(const QModelIndex & parent /*= QModelIndex() */) const
{
    if (!parent.isValid())
        return mRootItem->childCount();

    ModelItemPtr item = itemForIndex(parent);
	if (item)
		return item->childCount();
	else
        return 0;
}

int QtCommonModel::columnCount(const QModelIndex & parent /*= QModelIndex() */) const
{
    Q_UNUSED(parent)
	return mHeaders.size();
}

QVariant QtCommonModel::data(const QModelIndex & index, int role /*= Qt::DisplayRole */) const
{
    ModelItemPtr modelItem = itemForIndex(index);
	if (!modelItem)
		return QVariant();
	
	return modelItem->data(index.column(), role);
}

bool QtCommonModel::setData(const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
{
    ModelItemPtr modelItem = itemForIndex(index);
	if (modelItem && modelItem->setData(value, index.column(), role))
		return true;
	else
		return QAbstractItemModel::setData(index, value, role);
}

QModelIndex	QtCommonModel::index(int row, int column, const QModelIndex & parent /*= QModelIndex()*/) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

    ModelItemPtr parentItem = itemForIndex(parent);
	if (parentItem == nullptr)
        parentItem = mRootItem;

    ModelItemPtr childItem = parentItem->child(row);
	if (!childItem)
		return QModelIndex();
	else
        return createIndex(row, column, childItem);
}

Qt::ItemFlags QtCommonModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

    ModelItemPtr item = itemForIndex(index);
	if (item)
        return (Qt::ItemFlags)item->itemFlags(index.column());
	else
		return Qt::NoItemFlags;
}

QVariant QtCommonModel::headerData(int section, Qt::Orientation orientation, int role/* = Qt::DisplayRole */) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
		return mHeaders.at(section);
	else
		return QAbstractItemModel::headerData(section, orientation, role);
}

ModelItemPtr QtCommonModel::itemForIndex(const QModelIndex& index) const
{
	if (index.isValid())
        return mModelHash.value(index.internalPointer());
	else
        return ModelItemPtr();
}

void QtCommonModel::setHeaders(QStringList headers)
{
	mHeaders = headers;
}

void QtCommonModel::addItem(ModelItemPtr item, ModelItemPtr parent /*= nullptr*/)
{
    if (!item)
		return;

    if (!parent)
		parent = getRootItem();

	QModelIndex parentIndex = indexForItem(parent);
	int index = parent->childCount();
	beginInsertRows(parentIndex, index, index);
	parent->addChild(item);
	endInsertRows();
}

void QtCommonModel::insertItem(ModelItemPtr item, ModelItemPtr befor, ModelItemPtr parent /*= nullptr*/)
{
    if (!item)
		return;

    if (!parent)
		parent = getRootItem();

	QModelIndex parentIndex = indexForItem(parent);
	int index = parent->indexOf(befor);
	if (index < 0)
		index = parent->childCount();
	else
		index++;

	beginInsertRows(parentIndex, index, index);
	parent->insertChild(befor, item);
	endInsertRows();
}

void QtCommonModel::removeItem(ModelItemPtr item, ModelItemPtr parent)
{
	if (item == nullptr)
		return;

	QModelIndex index = indexForItem(item);
	beginRemoveRows(index, 0, 0);
	if (parent)
		parent->removeChild(item);
	else
		mRootItem->removeChild(item);
	endRemoveRows();
}

ModelItemPtr QtCommonModel::getRootItem() const
{
    return mRootItem;
}

QModelIndex QtCommonModel::indexForItem(ModelItemPtr item) const
{
	if (item == nullptr || item->parent() == nullptr)
		return QModelIndex();

    ModelItemPtr parent = item->parent();
	int row = parent->indexOf(item);
    return createIndex(row, 0, item);
}

QModelIndex QtCommonModel::createIndex(int row, int column, ModelItemPtr data) const
{
    void* key = data.data();
    mModelHash.insert(key,data);
    return QAbstractItemModel::createIndex(row,column,key);
}
