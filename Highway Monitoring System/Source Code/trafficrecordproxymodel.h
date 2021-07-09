#ifndef TRAFFICRECORDPROXYMODEL_H
#define TRAFFICRECORDPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QDateTime>
#include <QString>

class TrafficRecordProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit TrafficRecordProxyModel(QObject *parent = nullptr);

    void setPoleCode(QString poleCode);
    void setInterval(QDateTime start, QDateTime end);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QDateTime start;
    QDateTime end;
    QString poleCode;
};

#endif // TRAFFICRECORDPROXYMODEL_H
