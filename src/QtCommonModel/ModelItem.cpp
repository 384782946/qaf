#include "ModelItem.h"

ModelItem::ModelItem()
    :mParent(Q_NULLPTR)
	, mStatus(0)
{

}

ModelItem::~ModelItem(void)
{
	qDeleteAll(mChildren);
}

ModelItem* ModelItem::parent()
{
	return mParent;
}

int ModelItem::childCount()
{
	return mChildren.size();
}

void ModelItem::setStatus(int status)
{
	mStatus = status;
}

int ModelItem::status()
{
	return mStatus;
}

int ModelItem::indexOf(ModelItem* child)
{
	return mChildren.indexOf(child);
}

ModelItem* ModelItem::child(int index)
{
	if (index >= 0 && index < mChildren.size())
		return mChildren.at(index);
	else
		return nullptr;
}

QString ModelItem::className()
{
	return "ModelItem";
}

QList<QAction*> ModelItem::actions()
{
	return QList<QAction*>();
}

QVariant ModelItem::data(int index, int role)
{
	if (role == Qt::CheckStateRole)
		return mStatus;
	else
		return QVariant();
}

bool ModelItem::setData(const QVariant &value, int index, int role)
{
	if (role == Qt::CheckStateRole)
	{
		setStatus(value.toInt());
		return true;
	}
	return false;
}

void ModelItem::addChild(ModelItem* item)
{
	if (item){
		mChildren.append(item);
		item->mParent = this;
	}
}

void ModelItem::insertChild(ModelItem* befor, ModelItem* item)
{
	if (befor && item)
	{
		int beforeIndex = mChildren.indexOf(befor);
		if (beforeIndex != -1)
			mChildren.insert(beforeIndex, item);
		else
			mChildren.append(item);

		item->mParent = this;
	}
	else if (item)
	{
		mChildren.append(item);

		item->mParent = this;
	}
}

void ModelItem::removeChild(ModelItem* item)
{
	if (item){
		mChildren.removeOne(item);
		item->mParent = nullptr;
	}
}

int ModelItem::itemFlags(int)
{
	return Qt::ItemIsEnabled |
		Qt::ItemIsSelectable |
		Qt::ItemIsEditable |
		Qt::ItemIsTristate;
}
