#include "AbstractTreeModel.h"
#include "ModelItem.h"

namespace QAF
{
	AbstractTreeModel::AbstractTreeModel(QObject *parent)
		: QAbstractItemModel(parent)
		, mRootItem(new ModelItem())
	{

	}

	AbstractTreeModel::~AbstractTreeModel()
	{
		delete mRootItem;
	}

	QModelIndex	AbstractTreeModel::parent(const QModelIndex & index) const
	{
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

	int AbstractTreeModel::rowCount(const QModelIndex & parent /*= QModelIndex() */) const
	{
		if (!parent.isValid() && parent.column() > 0)
			return 0;

		ModelItem* item = itemForIndex(parent);
		if (item)
			return item->childCount();
		else
			return mRootItem->childCount();
	}

	int AbstractTreeModel::columnCount(const QModelIndex & parent /*= QModelIndex() */) const
	{
		return mHeaders.size();
	}

	QVariant AbstractTreeModel::data(const QModelIndex & index, int role /*= Qt::DisplayRole */) const
	{
		ModelItem* modelItem = itemForIndex(index);
		if (!modelItem)
			return QVariant();
		else
			return modelItem->data(index.column(), role);
	}

	bool AbstractTreeModel::setData(const QModelIndex &index, const QVariant &value, int role /*= Qt::EditRole*/)
	{
		ModelItem* modelItem = itemForIndex(index);
		if (modelItem && modelItem->setData(value, index.column(), role))
			return true;
		else
			return QAbstractItemModel::setData(index, value, role);
	}

	QModelIndex	AbstractTreeModel::index(int row, int column, const QModelIndex & parent /*= QModelIndex()*/) const
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

	Qt::ItemFlags AbstractTreeModel::flags(const QModelIndex &index) const
	{
		if (!index.isValid())
			return Qt::NoItemFlags;

		ModelItem* item = itemForIndex(index);
		if (item)
			return item->itemFlags(index.column());
		else
			return Qt::NoItemFlags;
	}

	QVariant AbstractTreeModel::headerData(int section, Qt::Orientation orientation, int role/* = Qt::DisplayRole */) const
	{
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
			return mHeaders.at(section);
		else
			return QAbstractItemModel::headerData(section, orientation, role);
	}

	ModelItem* AbstractTreeModel::itemForIndex(const QModelIndex& index) const
	{
		if (index.isValid())
			return static_cast<ModelItem*>(index.internalPointer());
		else
			return nullptr;
	}

	void AbstractTreeModel::setHeaders(QStringList headers)
	{
		mHeaders = headers;
	}

	void AbstractTreeModel::addItem(ModelItem* item, ModelItem* parent /*= nullptr*/)
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

	void AbstractTreeModel::insertItem(ModelItem* item, ModelItem* befor, ModelItem* parent /*= nullptr*/)
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

	void AbstractTreeModel::removeItem(ModelItem* item, ModelItem* parent)
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

	ModelItem* AbstractTreeModel::getRootItem() const
	{
		return mRootItem;
	}

	QModelIndex AbstractTreeModel::indexForItem(ModelItem* item) const
	{
		if (item == nullptr || item->parent() == nullptr)
			return QModelIndex();

		ModelItem* parent = item->parent();
		int row = parent->indexOf(item);
		return createIndex(row, 0, item);
	}
}