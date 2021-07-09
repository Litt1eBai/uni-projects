#ifndef LOCATIONFILTERPROXYMODEL_H
#define LOCATIONFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class LocationFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit LocationFilterProxyModel(QObject *parent = nullptr);
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const override;

private:
};

#endif // LOCATIONFILTERPROXYMODEL_H
