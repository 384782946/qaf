#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include "qafcore_global.h"
#include <QSortFilterProxyModel>

class QAFCORE_EXPORT MySortFilterProxyModel : public QSortFilterProxyModel
{
public:
    MySortFilterProxyModel(QObject *parent);
    ~MySortFilterProxyModel();

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // MYSORTFILTERPROXYMODEL_H