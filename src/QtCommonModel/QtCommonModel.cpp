#include "QtCommonModel.h"
#include "ModelItem.h"

QtCommonModel::QtCommonModel(QObject *parent)
	: QAbstractItemModel(parent)
	, mRootItem(new ModelItem())
{

}

QtCommonModel::~QtCommonModel()
{
	delete mRootItem;
    mRootItem = Q_NULLPTR;
}

int QtCommonModel::rowCount(const QModelIndex & parent /*= QModelIndex() */) const
{
	if (!parent.isValid() && parent.column() > 0)
		return 0;

	ModelItem* item = itemForIndex(parent);
	if (item)
		return item->childCount();
	else
		return mRootItem->childCount();
}

int QtCommonModel::columnCount(const QModelIndex & parent /*= QModelIndex() */) const
{
	return mHeaders.size();
}

QVariant QtCommonModel::data(const QModelIndex & index, int role /*= Qt::DisplayRole */) const
{
	ModelItem* modelItem = itemForIndex(index);
	if (!modelItem)
		return QVariant();
	
	return modelItem->data(index.column(), role);
}

bool QtCommonModel::setData(const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
{
	ModelItem* modelItem = itemForIndex(index);
	if (modelItem && modelItem->setData(value, index.column(), role))
		return true;
	else
		return QAbstractItemModel::setData(index, value, role);
}

QModelIndex	QtCommonModel::index(int row, int column, const QModelIndex & parent /*= QModelIndex()*/) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	ModelItem* parentItem = itemForIndex(parent);
	if (parentItem == nullptr)
		parentItem = mRootItem;

	ModelItem* childItem = parentItem->child(row);
	if (!childItem)
		return QModelIndex();
	else
		return createIndex(row, column, childItem);
}

QModelIndex	QtCommonModel::parent(const QModelIndex & index) const
{
    if (!index.isValid())
        return QModelIndex();

    ModelItem* item = itemForIndex(index);
    if (!item)
        return QModelIndex();

    ModelItem* parent = item->parent();
    if (!parent)
        return QModelIndex();

    ModelItem* grandparent = parent->parent();
    if (!grandparent)
        return QModelIndex();

    int row = grandparent->indexOf(parent);
    return createIndex(row, 0, parent);
}

Qt::ItemFlags QtCommonModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::NoItemFlags;

	ModelItem* item = itemForIndex(index);
	if (item)
        return (Qt::ItemFlags)(item->itemFlags(index.column()));
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

ModelItem* QtCommonModel::itemForIndex(const QModelIndex& index) const
{
	if (index.isValid())
		return static_cast<ModelItem*>(index.internalPointer());
	else
        return mRootItem;
}

void QtCommonModel::setHeaders(const QStringList& headers)
{
	mHeaders = headers;
}

void QtCommonModel::addItem(ModelItem* item, ModelItem* parent /*= nullptr*/)
{
	if (item == nullptr)
		return;

	if (parent == nullptr)
		parent = getRootItem();

	QModelIndex parentIndex = indexForItem(parent);
	int index = parent->childCount();
	beginInsertRows(parentIndex, index, index);
	parent->addChild(item);
	endInsertRows();
}

void QtCommonModel::insertItem(ModelItem* item, ModelItem* befor, ModelItem* parent /*= nullptr*/)
{
	if (item == nullptr)
		return;

	if (parent == nullptr)
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

void QtCommonModel::removeItem(ModelItem* item)
{
	if (item == nullptr)
		return;

	QModelIndex index = indexForItem(item);
    QModelIndex parentIndex = index.parent();
    beginRemoveRows(parentIndex, index.row(), index.row());
    if (parentIndex.isValid()){
        ModelItem* parent = itemForIndex(parentIndex);
        if(parent) parent->removeChild(item);
    }else
		mRootItem->removeChild(item);
    endRemoveRows();
}

void QtCommonModel::addItems(QList<ModelItem*> items, ModelItem *parent)
{
    if (items.size() == 0)
        return;

    if (parent == nullptr)
        parent = getRootItem();

    QModelIndex parentIndex = indexForItem(parent);
    int index = parent->childCount();

    beginInsertRows(parentIndex, index, index + items.size() - 1);
    foreach(auto item,items) {
        parent->addChild(item);
    }
    endInsertRows();
}

void QtCommonModel::clearChildren(ModelItem *parent)
{
    if (parent == nullptr)
        return;

    if(parent->childCount() <= 0)
        return;

    QModelIndex parentIndex =  this->indexForItem(parent);
    beginRemoveRows(parentIndex, 0, parent->childCount());
    parent->clearChildren();
    endRemoveRows();
}

ModelItem* QtCommonModel::getRootItem() const
{
    return mRootItem;
}

void QtCommonModel::notifyDataChange(const QModelIndex &index, int role)
{
    emit this->dataChanged(index,index);
}

QModelIndex QtCommonModel::indexForItem(ModelItem* item) const
{
	if (item == nullptr || item->parent() == nullptr)
		return QModelIndex();

	ModelItem* parent = item->parent();
	int row = parent->indexOf(item);
	return createIndex(row, 0, item);
}
