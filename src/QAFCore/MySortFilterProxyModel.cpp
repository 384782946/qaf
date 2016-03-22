#include "MySortFilterProxyModel.h"
#include "ModelItem.h"

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

MySortFilterProxyModel::~MySortFilterProxyModel()
{

}

bool MySortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
	if (!source_parent.isValid())
		return true;

    if (!filterRegExp().isValid() || filterRegExp().isEmpty())
        return true;

    bool filter = true;
    QModelIndex source_index = sourceModel()->index(source_row,0,source_parent);
    ModelItem* item = static_cast<ModelItem*>(source_index.internalPointer());
    filter = QSortFilterProxyModel::filterAcceptsRow(source_row,source_parent);
    if(filter)
    {
        return true;
    }
    else
    {
        for (int k =0;k<sourceModel()->rowCount(source_index);k++)
        {
            if(filterAcceptsRow(k,source_index))
            {
                return true;
            }
        }
    }

    return false;
}