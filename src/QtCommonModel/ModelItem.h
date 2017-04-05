#pragma once

#include <QObject>
#include <QList>
#include <QVariant>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QEnableSharedFromThis>
#include "qtcommonmodel_global.h"
#include <memory>


class ModelItem;
class QAction;

typedef QSharedPointer<ModelItem> ModelItemPtr;
typedef QWeakPointer<ModelItem> ModelItemWeekRef;

class QTCOMMONMODEL_EXPORT ModelItem:public QEnableSharedFromThis<ModelItem>
{
public:
    explicit ModelItem(ModelItemPtr parent = ModelItemPtr());
    virtual ~ModelItem(){}

    //method for qtcommonmodel
    virtual QString className() const = 0;
    virtual QVariant data(int index, int role = Qt::DisplayRole) const;
	virtual bool setData(const QVariant &value, int index, int role = Qt::DisplayRole);
    virtual int itemFlags(int index) const;
    virtual QList<QAction*> actions() const;

    ModelItemPtr parent() const;
    int childCount() const;
    int indexOf(ModelItemPtr) const;
    ModelItemPtr child(int) const;

    void addChild(ModelItemPtr);
    void insertChild(ModelItemPtr befor, ModelItemPtr item);
    void removeChild(ModelItemPtr);

    //int status() const;
    //void setStatus(int);

private:
    QList<ModelItemPtr> mChildren;
    ModelItemWeekRef mParent;
    //int mStatus;
};
