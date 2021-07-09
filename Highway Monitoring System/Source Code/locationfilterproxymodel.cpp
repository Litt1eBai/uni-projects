#include "locationfilterproxymodel.h"
#include "polemodel.h"

LocationFilterProxyModel::LocationFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

bool LocationFilterProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    if (source_column == PoleModel::Description || source_column == PoleModel::PoleCode) {
        return true;
    } else {
        return false;
    }
}
