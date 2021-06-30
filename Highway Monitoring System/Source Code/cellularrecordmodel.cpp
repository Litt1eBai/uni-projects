#include "cellularrecordmodel.h"
#include <QDebug>

CellularRecordModel::CellularRecordModel(QObject *parent)
    : QAbstractTableModel(parent)
{

    setupModel();

}

QVariant CellularRecordModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case CellularRecordModel::RecordNo: return QString("Record #");
            case CellularRecordModel::DeviceCode: return QString("Device Code");
            case CellularRecordModel::PoleCode: return QString("Pole Code");
            case CellularRecordModel::IMEI: return QString("IMEI");
            case CellularRecordModel::RecordTime: return QString("Record Time");
        }
    } else {
        return QStringLiteral("%1").arg(section);
    }
    return QVariant();
}

int CellularRecordModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->m_cellularRecordData.size();
}

int CellularRecordModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 5;
}

QVariant CellularRecordModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole: {
            switch (index.column()) {
                case CellularRecordModel::RecordNo: return m_cellularRecordData.at(index.row()).getRecordNo();
                case CellularRecordModel::DeviceCode: return m_cellularRecordData.at(index.row()).getDeviceCode();
                case CellularRecordModel::PoleCode: return m_cellularRecordData.at(index.row()).getPoleCode();
                case CellularRecordModel::IMEI: return m_cellularRecordData.at(index.row()).getIMEI();
                case CellularRecordModel::RecordTime: return m_cellularRecordData.at(index.row()).getRecordTime();
            }
        }
    }

    return QVariant();
}

bool CellularRecordModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "[Debug]: setData Function called";

    if (data(index, role) != value) {

        if (role == Qt::EditRole) {
            if (!checkIndex(index))
                return false;

            qDebug() << "[Debug]: setting Data";
            switch (index.column()) {
                case CellularRecordModel::RecordNo: {
                    QString val = value.toString();
                    this->m_cellularRecordData[index.row()].setRecoedNo((char*)val.toStdString().c_str());
                    break;
                }

                case CellularRecordModel::DeviceCode: {
                    QString val = value.toString();
                    this->m_cellularRecordData[index.row()].setDeviceCode((char*)val.toStdString().c_str());
                    break;
                }

                case CellularRecordModel::PoleCode: {
                    QString val = value.toString();
                    this->m_cellularRecordData[index.row()].setPoleCode((char*)val.toStdString().c_str());
                    break;
                }

                case CellularRecordModel::IMEI: {
                    QString val = value.toString();
                    this->m_cellularRecordData[index.row()].setIMEI((char*)val.toStdString().c_str());
                    break;
                }

                case CellularRecordModel::RecordTime: {
                    QDateTime val = QDateTime::fromString(value.toString(), "dd/MM/yyyy hh:mm");
                    this->m_cellularRecordData[index.row()].setRecordTime(val);
                    break;
                }

            }
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags CellularRecordModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

void CellularRecordModel::sort(int column, Qt::SortOrder order)
{
    beginResetModel();

    std::sort(this->m_cellularRecordData.begin(), this->m_cellularRecordData.end(),
          [=](const CellularRecord &cr1, const CellularRecord& cr2){
        switch (column) {
            case (int)CellularRecordModel::RecordNo: {
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
            case (int)CellularRecordModel::DeviceCode: {
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
            case (int)CellularRecordModel::PoleCode: {
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
            case (int)CellularRecordModel::IMEI: {
                if (order == Qt::AscendingOrder) {
                    if (cr1.getIMEI() > cr2.getIMEI()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (cr1.getIMEI() < cr2.getIMEI()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)CellularRecordModel::RecordTime: {
                if (order == Qt::AscendingOrder) {
                    if (cr1.getRecordTime() > cr2.getRecordTime()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (cr1.getRecordTime() < cr2.getRecordTime()) {
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

void CellularRecordModel::setupModel()
{
    CellularRecord record1("L0831807012", "K31+950", "0");
    record1.setIMEI("460115455495254");
    this->m_cellularRecordData.append(record1);
}

void CellularRecordModel::appendRow(CellularRecord newRow, const QModelIndex &parent)
{
    int row = this->rowCount();
    beginInsertRows(parent, row, row);
    this->m_cellularRecordData.append(newRow);
    endInsertRows();
}

void CellularRecordModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    if (row < 0 || row > this->m_cellularRecordData.size()) {
        qDebug() << "Invalid Index";
    } else {
        this->m_cellularRecordData.erase(this->m_cellularRecordData.begin() + row);
    }
    endRemoveRows();
}

QVector<CellularRecord> CellularRecordModel::getRecordData()
{
    QVector<CellularRecord> record = this->m_cellularRecordData;
    return record;
}

int CellularRecordModel::findRecord_getIndex(QString recordNo)
{
    for (int i = 0; i < this->m_cellularRecordData.size(); i++) {
        if (this->m_cellularRecordData.at(i).getRecordNo() == recordNo) return i;
    }
    return -1;
}

int CellularRecordModel::totalRecords()
{
    return this->m_cellularRecordData.size();
}

void CellularRecordModel::setUpdatedData(CellularRecord updatedData, const QModelIndex &indexOfData)
{

    if (indexOfData.row() >= this->m_cellularRecordData.size()) {
        return;
    }

    if (this->m_cellularRecordData[indexOfData.row()].getRecordNo() != updatedData.getRecordNo()) {
        char *newRecordNo = new char[c_recordCodeDigit];
        updatedData.getRecordNo(newRecordNo);
        this->m_cellularRecordData[indexOfData.row()].setRecoedNo(newRecordNo);
    }
    if (this->m_cellularRecordData[indexOfData.row()].getDeviceCode() != updatedData.getDeviceCode()) {
        char *newDeviceCode = new char[c_DeviceCodeDiget];
        updatedData.getRecordNo(newDeviceCode);
        this->m_cellularRecordData[indexOfData.row()].setDeviceCode(newDeviceCode);
    }
    if (this->m_cellularRecordData[indexOfData.row()].getPoleCode() != updatedData.getPoleCode()) {
        char *newPoleCode = new char[c_PoleCodeDigit];
        updatedData.getRecordNo(newPoleCode);
        this->m_cellularRecordData[indexOfData.row()].setPoleCode(newPoleCode);
    }
    if (this->m_cellularRecordData[indexOfData.row()].getIMEI() != updatedData.getIMEI()) {
        char *newIMEI = new char[c_IMEIDigit];
        updatedData.getRecordNo(newIMEI);
        this->m_cellularRecordData[indexOfData.row()].setIMEI(newIMEI);
    }
    if (this->m_cellularRecordData[indexOfData.row()].getRecordTime() != updatedData.getRecordTime()) {
        QDateTime newRecordTime = updatedData.getRecordTime();
        this->m_cellularRecordData[indexOfData.row()].setRecordTime(newRecordTime);
    }

    emit dataChanged(indexOfData, indexOfData, QVector<int>() << Qt::EditRole);
}

