#include "cctvrecordmodel.h"
#include "cctvrecord.h"
#include <QDebug>

CCTVRecordModel::CCTVRecordModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    setupModel();
}

QVariant CCTVRecordModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case CCTVRecordModel::RecordNo: return QString("Record #");
            case CCTVRecordModel::DeviceCode: return QString("Device Code");
            case CCTVRecordModel::PoleCode: return QString("Pole Code");
            case CCTVRecordModel::Description: return QString("Description");
            case CCTVRecordModel::FilePath: return QString("FilePath");
            case CCTVRecordModel::StartTime: return QString("Start Time");
            case CCTVRecordModel::EndTime: return QString("End Time");
        }
    } else {
        return QStringLiteral("%1").arg(section);
    }
    return QVariant();
}

int CCTVRecordModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->m_CCTVRecordData.size();
}

int CCTVRecordModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 7;
}

QVariant CCTVRecordModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole: {
            switch (index.column()) {
                case CCTVRecordModel::RecordNo: return m_CCTVRecordData.at(index.row()).getRecordNo();
                case CCTVRecordModel::DeviceCode: return m_CCTVRecordData.at(index.row()).getDeviceCode();
                case CCTVRecordModel::PoleCode: return m_CCTVRecordData.at(index.row()).getPoleCode();
                case CCTVRecordModel::Description: return m_CCTVRecordData.at(index.row()).getDescription();
                case CCTVRecordModel::StartTime: return m_CCTVRecordData.at(index.row()).getStartTime();
                case CCTVRecordModel::EndTime: return m_CCTVRecordData.at(index.row()).getEndTime();
                case CCTVRecordModel::FilePath: return m_CCTVRecordData.at(index.row()).getFilePath();
            }
        }
    }
    return QVariant();
}

bool CCTVRecordModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "[Debug]: setData Function called";

    if (data(index, role) != value) {

        if (role == Qt::EditRole) {
            if (!checkIndex(index))
                return false;

            qDebug() << "[Debug]: setting Data";
            switch (index.column()) {
                case CCTVRecordModel::RecordNo: {
                    QString val = value.toString();
                    this->m_CCTVRecordData[index.row()].setRecoedNo((char*)val.toStdString().c_str());
                    break;
                }

                case CCTVRecordModel::DeviceCode: {
                    QString val = value.toString();
                    this->m_CCTVRecordData[index.row()].setDeviceCode((char*)val.toStdString().c_str());
                    break;
                }

                case CCTVRecordModel::PoleCode: {
                    QString val = value.toString();
                    this->m_CCTVRecordData[index.row()].setPoleCode((char*)val.toStdString().c_str());
                    break;
                }

                case CCTVRecordModel::Description: {
                    QString val = value.toString();
                    this->m_CCTVRecordData[index.row()].setDescription((char*)val.toStdString().c_str());
                    break;
                }

                case CCTVRecordModel::StartTime: {
                    QDateTime val = QDateTime::fromString(value.toString(), "dd/MM/yyyy hh:mm");
                    this->m_CCTVRecordData[index.row()].setStartTime(val);
                    break;
                }

                case CCTVRecordModel::EndTime: {
                    QDateTime val = QDateTime::fromString(value.toString(), "dd/MM/yyyy hh:mm");
                    this->m_CCTVRecordData[index.row()].setEndTime(val);
                    break;
                }

                case CCTVRecordModel::FilePath: {
                    QString val = value.toString();
                    this->m_CCTVRecordData[index.row()].setFilePath((char*)val.toStdString().c_str());
                    break;
                }
            }
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CCTVRecordModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

void CCTVRecordModel::sort(int column, Qt::SortOrder order)
{
    beginResetModel();

    std::sort(this->m_CCTVRecordData.begin(), this->m_CCTVRecordData.end(),
          [=](const CCTVRecord& cr1, const CCTVRecord& cr2){
        switch (column) {
            case (int)CCTVRecordModel::RecordNo: {
                if (order == Qt::AscendingOrder) {
                    if (cr1.getRecordNo() > cr2.getRecordNo()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (cr1.getRecordNo() < cr2.getRecordNo()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)CCTVRecordModel::DeviceCode: {
                if (order == Qt::AscendingOrder) {
                    if (cr1.getDeviceCode() > cr2.getDeviceCode()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (cr1.getDeviceCode() < cr2.getDeviceCode()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)CCTVRecordModel::PoleCode: {
                if (order == Qt::AscendingOrder) {
                    if (cr1.getPoleCode() > cr2.getPoleCode()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (cr1.getPoleCode() < cr2.getPoleCode()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)CCTVRecordModel::Description: {
                if (order == Qt::AscendingOrder) {
                    if (cr1.getDescription() > cr2.getDescription()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (cr1.getDescription() < cr2.getDescription()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)CCTVRecordModel::StartTime: {
                if (order == Qt::AscendingOrder) {
                    if (cr1.getStartTime() > cr2.getStartTime()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (cr1.getStartTime() < cr2.getStartTime()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)CCTVRecordModel::EndTime: {
                if (order == Qt::AscendingOrder) {
                    if (cr1.getEndTime() > cr2.getEndTime()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (cr1.getEndTime() < cr2.getEndTime()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
                // in case
            default: return false;
        }
        // in case
        return false;
    });

    endResetModel();
}

void CCTVRecordModel::setupModel()
{
    CCTVRecord cctvRecord;
    this->m_CCTVRecordData.append(cctvRecord);
}

void CCTVRecordModel::appendRow(CCTVRecord newRow, const QModelIndex &parent)
{
    int row = this->rowCount();
    beginInsertRows(parent, row, row);
    this->m_CCTVRecordData.append(newRow);
    endInsertRows();
}

void CCTVRecordModel::removeRow(int row, const QModelIndex &parent)
{
    if (row < 0 || row > this->m_CCTVRecordData.size()) {
        qDebug() << "Invalid Index";
    } else {
        beginRemoveRows(parent, row, row);
        this->m_CCTVRecordData.erase(this->m_CCTVRecordData.begin() + row);
        endRemoveRows();
    }
}

QVector<CCTVRecord> CCTVRecordModel::getRecordData()
{
    QVector<CCTVRecord> record = this->m_CCTVRecordData;
    return record;
}

int CCTVRecordModel::findRecord_getIndex(QString recordNo)
{
    for (int i = 0; i < this->m_CCTVRecordData.size(); i++) {
        if (this->m_CCTVRecordData.at(i).getRecordNo() == recordNo) return i;
    }
    return -1;
}

CCTVRecord CCTVRecordModel::getCurrentRecord(int row)
{
    CCTVRecord record;
    if (row >= 0 && row < this->m_CCTVRecordData.size()) {
        record = this->m_CCTVRecordData.at(row);
    } else {
        record.setFilePath((char*)"");
    }

    return record;
}

int CCTVRecordModel::totalRecords()
{
    return this->m_CCTVRecordData.size();

}
