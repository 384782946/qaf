/*!
 * \file AbstractTreeModel.h
 * \date 2016/01/16 14:25
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * 基于Qt MVC模式实现的树形结构模型，实现了以行为单位的模型
 * 相比QStandardItem以单元格为单位的模型，该模型更适数据粒度稍大的需求
 *
 * \note
*/

#ifndef ABSTRACTTREEMODEL_H
#define ABSTRACTTREEMODEL_H

#include <QAbstractItemModel>
#include <QStringList>
#include <QHash>

#include "qtcommonmodel_global.h"
#include "ModelItem.h"

class RootItem:public ModelItem{
    virtual QString className() const{
        return "RootItem";
    }

    ModelItemPtr parent() const{
        return ModelItemPtr();
    }

    virtual QVariant data(int, int) const{return QVariant();}
};

class QTCOMMONMODEL_EXPORT QtCommonModel : public QAbstractItemModel
{
public:
	QtCommonModel(QObject *parent = nullptr);
	virtual ~QtCommonModel();

	virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;
	virtual int	columnCount(const QModelIndex & parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
	virtual QModelIndex	parent(const QModelIndex & index) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;

	void setHeaders(QStringList headers);
    void addItem(ModelItemPtr item, ModelItemPtr parent = ModelItemPtr());
    void insertItem(ModelItemPtr item, ModelItemPtr befor, ModelItemPtr parent = ModelItemPtr());
    void removeItem(ModelItemPtr item, ModelItemPtr parent = ModelItemPtr());

    QModelIndex indexForItem(ModelItemPtr item) const;
    ModelItemPtr itemForIndex(const QModelIndex& index) const;

protected:
    QModelIndex createIndex(int row, int column, ModelItemPtr data) const;
    ModelItemPtr getRootItem() const;

private:
	QStringList mHeaders;
    ModelItemPtr mRootItem;
    mutable QHash<void*,ModelItemPtr> mModelHash;
};

#endif // ABSTRACTTREEMODEL_H
