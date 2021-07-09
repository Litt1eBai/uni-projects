#include "cellularrecordproxymodel.h"
#include "cellularrecordmodel.h"
#include <QVariant>
#include <QDebug>

CellularRecordProxyModel::CellularRecordProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    this->end = QDateTime().currentDateTime();
    this->start = QDateTime().currentDateTime().addDays(-1);
    this->poleCode = "";
}

void CellularRecordProxyModel::setPoleCode(QString poleCode)
{
    beginResetModel();
    this->poleCode = poleCode;
    endResetModel();
}

void CellularRecordProxyModel::setInterval(QDateTime start, QDateTime end)
{
    beginResetModel();
    this->start = start;
    this->end = end;
    endResetModel();
}

bool CellularRecordProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex poleCodeIndex = sourceModel()->index(source_row, CellularRecordModel::PoleCode, source_parent);
    QModelIndex timeIndex = sourceModel()->index(source_row, CellularRecordModel::RecordTime, source_parent);
    QDateTime time = QVariant(sourceModel()->data(timeIndex)).toDateTime();
    QString poleCode = QVariant(sourceModel()->data(poleCodeIndex)).toString();

    if (poleCode == this->poleCode || this->poleCode == "") {
        if (time >= start && time <= end) {
            return true;
        }
    }
    return false;
}
