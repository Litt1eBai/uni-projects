#include "trafficrecordproxymodel.h"
#include "trafficrecordmodel.h"
#include <QVariant>
#include <QDebug>

TrafficRecordProxyModel::TrafficRecordProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    this->end = QDateTime().currentDateTime();
    this->start = QDateTime().currentDateTime().addDays(-1);
    this->poleCode = "";
}

void TrafficRecordProxyModel::setPoleCode(QString poleCode)
{
    beginResetModel();
    this->poleCode = poleCode;
    endResetModel();
}

void TrafficRecordProxyModel::setInterval(QDateTime start, QDateTime end)
{
    beginResetModel();
    this->start = start;
    this->end = end;
    endResetModel();
}

bool TrafficRecordProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex poleCodeIndex = sourceModel()->index(source_row, TrafficRecordModel::PoleCode, source_parent);
    QModelIndex timeIndex = sourceModel()->index(source_row, TrafficRecordModel::RecordTime, source_parent);
    QDateTime time = QVariant(sourceModel()->data(timeIndex)).toDateTime();
    QString currentPoleCode = QVariant(sourceModel()->data(poleCodeIndex)).toString();
    if (currentPoleCode == this->poleCode || this->poleCode == "") {
        if (time >= start && time <= end) {
            return true;
        }
    }
    return false;
}
