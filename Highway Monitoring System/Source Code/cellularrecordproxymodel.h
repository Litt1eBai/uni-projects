#ifndef CELLULARRECORDPROXYMODEL_H
#define CELLULARRECORDPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QDateTime>
#include <QString>

class CellularRecordProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit CellularRecordProxyModel(QObject *parent = nullptr);

    void setPoleCode(QString poleCode);
    void setInterval(QDateTime start, QDateTime end);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:

    QDateTime start;
    QDateTime end;
    QString poleCode;
};

#endif // CELLULARRECORDPROXYMODEL_H
