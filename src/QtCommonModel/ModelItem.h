#ifndef MODELITEM_H
#define MODELITEM_H

#include <QList>
#include <QVariant>
#include "qtcommonmodel_global.h"

class QAction;

class QTCOMMONMODEL_EXPORT ModelItem
{
    friend class QtCommonModel;
public:
	ModelItem();
	virtual ~ModelItem();

	virtual QString className();
	virtual QVariant data(int index, int role = Qt::DisplayRole);
	virtual bool setData(const QVariant &value, int index, int role = Qt::DisplayRole);
	virtual int itemFlags(int index);
	virtual QList<QAction*> actions();

	ModelItem* parent();
	int childCount();
	int indexOf(ModelItem*);
	ModelItem* child(int);

	void setStatus(int);
	int status();

protected: //item之间的关系需要通过model来维护
    void addChild(ModelItem*);
    void insertChild(ModelItem* befor, ModelItem* item);
    void removeChild(ModelItem*);
    void clearChildren();

private:
	QList<ModelItem*> mChildren;
	ModelItem* mParent;
	int mStatus;
};

#endif //MODELITEM_H
