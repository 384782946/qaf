#include "ModelItem.h"

ModelItem::ModelItem(ModelItemPtr parent)
    :mParent(parent)
    //, mStatus(0)
{

}

ModelItemPtr ModelItem::parent() const
{
    return mParent.toStrongRef();
}

int ModelItem::childCount() const
{
    return mChildren.size();
}

int ModelItem::indexOf(ModelItemPtr child) const
{
    return mChildren.indexOf(child);
}

ModelItemPtr ModelItem::child(int index) const
{
    if (index >= 0 && index < mChildren.size())
        return mChildren.at(index);
	else
        return ModelItemPtr();
}

QString ModelItem::className() const
{
    return "ModelItem";
}

QList<QAction*> ModelItem::actions() const
{
	return QList<QAction*>();
}

QVariant ModelItem::data(int,int) const
{
    return QVariant();
}

bool ModelItem::setData(const QVariant &, int, int)
{
	return false;
}

void ModelItem::addChild(ModelItemPtr item)
{
    if (item){
        mChildren.append(item);
        item->mParent = sharedFromThis().toWeakRef();
	}
}

void ModelItem::insertChild(ModelItemPtr befor, ModelItemPtr item)
{
    if (befor && item)
    {
        int beforeIndex = mChildren.indexOf(befor);
        if (beforeIndex != -1)
            mChildren.insert(beforeIndex, item);
        else
            mChildren.append(item);

        item->mParent = sharedFromThis().toWeakRef();
    }
    else if (item)
    {
        mChildren.append(item);
        item->mParent = sharedFromThis().toWeakRef();
    }
}

void ModelItem::removeChild(ModelItemPtr item)
{
    if (item){
        mChildren.removeOne(item);
        item->mParent.clear();
	}
}

int ModelItem::itemFlags(int) const
{
	return Qt::ItemIsEnabled |
		Qt::ItemIsSelectable |
        Qt::ItemIsEditable |
		Qt::ItemIsTristate;
}
