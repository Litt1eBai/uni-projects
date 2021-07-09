#include "cctvrecordproxymodel.h"
#include "cctvrecordmodel.h"

CCTVRecordProxyModel::CCTVRecordProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    this->end = QDateTime().currentDateTime();
    this->start = QDateTime().currentDateTime().addDays(-1);
    this->poleCode = "";
}

void CCTVRecordProxyModel::setPoleCode(QString poleCode)
{
    beginResetModel();
    this->poleCode = poleCode;
    endResetModel();
}

void CCTVRecordProxyModel::setInterval(QDateTime start, QDateTime end)
{
    beginResetModel();
    this->start = start;
    this->end = end;
    endResetModel();
}

bool CCTVRecordProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex poleCodeIndex = sourceModel()->index(source_row, CCTVRecordModel::PoleCode, source_parent);
    QModelIndex timeIndex = sourceModel()->index(source_row, CCTVRecordModel::StartTime, source_parent);
    QDateTime time = QVariant(sourceModel()->data(timeIndex)).toDateTime();
    QString poleCode = QVariant(sourceModel()->data(poleCodeIndex)).toString();

    if (poleCode == this->poleCode || this->poleCode == "") {
        if (time >= start && time <= end) {
            return true;
        }
    }
    return false;
}

bool CCTVRecordProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    if (source_column == CCTVRecordModel::FilePath) {
        return false;
    } else {
        return true;
    }
}
