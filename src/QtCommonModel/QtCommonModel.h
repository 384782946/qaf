/*!
 * \file AbstractTreeModel.h
 * \date 2016/01/16 14:25
 *
 * \author zxj
 * Contact: user@company.com
 *
 * \brief 
 *
 * ����Qt MVCģʽʵ�ֵ����νṹģ�ͣ�ʵ��������Ϊ��λ��ģ��
 * ���QStandardItem�Ե�Ԫ��Ϊ��λ��ģ�ͣ���ģ�͸������������Դ������
 *
 * \note
*/

#ifndef ABSTRACTTREEMODEL_H
#define ABSTRACTTREEMODEL_H

#include <QAbstractItemModel>
#include <QStringList>

#include "qtcommonmodel_global.h"

class ModelItem;

class QTCOMMONMODEL_EXPORT QtCommonModel : public QAbstractItemModel
{
public:
    QtCommonModel(QObject *parent = Q_NULLPTR);
	virtual ~QtCommonModel();

	virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;
	virtual int	columnCount(const QModelIndex & parent = QModelIndex()) const;
	virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
	virtual QModelIndex	parent(const QModelIndex & index) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual Qt::ItemFlags flags(const QModelIndex &index) const;

    void setHeaders(const QStringList& headers);
    void addItem(ModelItem* item, ModelItem* parent = Q_NULLPTR);
    void insertItem(ModelItem* item, ModelItem* befor, ModelItem* parent = Q_NULLPTR);
    void removeItem(ModelItem* item);

	QModelIndex indexForItem(ModelItem* item) const;
	ModelItem* itemForIndex(const QModelIndex& index) const;
	ModelItem* getRootItem() const;
private:
	QStringList mHeaders;
    ModelItem* mRootItem;
};

#endif // ABSTRACTTREEMODEL_H
