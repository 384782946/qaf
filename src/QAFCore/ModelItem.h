#pragma once

#include <QList>
#include <QVariant>

class QAction;

#include "qafcore_global.h"

class QAFCORE_EXPORT ModelItem
{
public:
    ModelItem();
    virtual ~ModelItem();

    virtual QString className();
	virtual QVariant data(int index, int role = Qt::DisplayRole);
	virtual bool setData(const QVariant &value, int index, int role = Qt::DisplayRole);
	virtual int itemFlags(int index);
	virtual QList<QAction*> actions();

    ModelItem* parent();
	void addChild(ModelItem*);
	void insertChild(ModelItem* befor, ModelItem* item);
	void removeChild(ModelItem*);
    int childCount();
    int indexOf(ModelItem*);
    ModelItem* child(int);
    
    void setStatus(int);
    int status();

private:
	QList<ModelItem*> mChildren;
    ModelItem* mParent;
    int mStatus;
};