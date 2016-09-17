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

#include "qafcore_global.h"

namespace QAF
{
	class ModelItem;

	class QAFCORE_EXPORT CommonTreeModel : public QAbstractItemModel
	{
	public:
		CommonTreeModel(QObject *parent = nullptr);
		virtual ~CommonTreeModel();

		virtual int	rowCount(const QModelIndex & parent = QModelIndex()) const;
		virtual int	columnCount(const QModelIndex & parent = QModelIndex()) const;
		virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
		virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
		virtual QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
		virtual QModelIndex	parent(const QModelIndex & index) const;
		virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		virtual Qt::ItemFlags flags(const QModelIndex &index) const;

		void setHeaders(QStringList headers);
		void addItem(ModelItem* item, ModelItem* parent = nullptr);
		void insertItem(ModelItem* item, ModelItem* befor, ModelItem* parent = nullptr);
		void removeItem(ModelItem* item, ModelItem* parent = nullptr);

		QModelIndex indexForItem(ModelItem* item) const;
		ModelItem* itemForIndex(const QModelIndex& index) const;
		ModelItem* getRootItem() const;
	private:
		QStringList mHeaders;
		ModelItem* mRootItem = nullptr;
	};
}

#endif // ABSTRACTTREEMODEL_H