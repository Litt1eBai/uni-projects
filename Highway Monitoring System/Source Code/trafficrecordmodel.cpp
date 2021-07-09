#include "trafficrecordmodel.h"
#include <QDebug>

TrafficRecordModel::TrafficRecordModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    setupModel();
}

QVariant TrafficRecordModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case TrafficRecordModel::RecordNo: return QString("Record #");
            case TrafficRecordModel::DeviceCode: return QString("Device Code");
            case TrafficRecordModel::PoleCode: return QString("Pole Code");
//            case TrafficRecordModel::VehicleColour: return QString("Colour");
//            case TrafficRecordModel::VehicleRegion: return QString("Region");
            case TrafficRecordModel::VehicleRegistrationNo: return QString("Registration No");
//            case TrafficRecordModel::VehicleRegistrationType: return QString("Registration Type");
            case TrafficRecordModel::VehicleSpeed: return QString("Speed");
            case TrafficRecordModel::RecordTime: return QString("Record Time");
        }
    } else {
        return QStringLiteral("%1").arg(section);
    }
    return QVariant();
}

int TrafficRecordModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->m_trafficRecordData.size();
}

int TrafficRecordModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 6;
//    return 7;
}

QVariant TrafficRecordModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole: {
            switch (index.column()) {
                case TrafficRecordModel::RecordNo: return this->m_trafficRecordData.at(index.row()).getRecordNo();
                case TrafficRecordModel::DeviceCode: return this->m_trafficRecordData.at(index.row()).getDeviceCode();
                case TrafficRecordModel::PoleCode: return this->m_trafficRecordData.at(index.row()).getPoleCode();
//                case TrafficRecordModel::VehicleColour: {
//                    switch (this->m_trafficRecordData.at(index.row()).getVehicleColour()) {

//                    }
//                }
//                case TrafficRecordModel::VehicleRegion: {
//                    switch (this->m_trafficRecordData.at(index.row()).getRegistrationRegion()) {

//                    }
//                }
                case TrafficRecordModel::VehicleRegistrationNo: return this->m_trafficRecordData.at(index.row()).getVehicleRegistrationNo();
//                case TrafficRecordModel::VehicleRegistrationType: {
//                    switch (this->m_trafficRecordData.at(index.row()).getRegistrationType()) {

//                    }
//                }
                case TrafficRecordModel::VehicleSpeed: return QVariant(this->m_trafficRecordData.at(index.row()).getSpeed()).toString();
                case TrafficRecordModel::RecordTime: return this->m_trafficRecordData.at(index.row()).getRecordTime();
            }
        }
    }
    return QVariant();
}

bool TrafficRecordModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (data(index, role) != value) {

        if (role == Qt::EditRole) {
            if (!checkIndex(index))
                return false;

            switch (index.column()) {
                case TrafficRecordModel::RecordNo: {
                    QString val = value.toString();
                    this->m_trafficRecordData[index.row()].setRecoedNo((char*)val.toStdString().c_str());
                    break;
                }

                case TrafficRecordModel::DeviceCode: {
                    QString val = value.toString();
                    this->m_trafficRecordData[index.row()].setDeviceCode((char*)val.toStdString().c_str());
                    break;
                }

                case TrafficRecordModel::PoleCode: {
                    QString val = value.toString();
                    this->m_trafficRecordData[index.row()].setPoleCode((char*)val.toStdString().c_str());
                    break;
                }

                case TrafficRecordModel::VehicleRegistrationNo: {
                    QString val = value.toString();
                    this->m_trafficRecordData[index.row()].setRegistrationNo((char*)val.toStdString().c_str());
                    break;
                }
                case TrafficRecordModel::VehicleSpeed: {
                    double val = value.toDouble();
                    this->m_trafficRecordData[index.row()].setSpeed(val);
                }

                case TrafficRecordModel::RecordTime: {
                    QDateTime val = QDateTime::fromString(value.toString(), "dd/MM/yyyy hh:mm");
                    this->m_trafficRecordData[index.row()].setRecordTime(val);
                    break;
                }
            }
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TrafficRecordModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

void TrafficRecordModel::sort(int column, Qt::SortOrder order)
{
    beginResetModel();

    std::sort(this->m_trafficRecordData.begin(), this->m_trafficRecordData.end(),
          [=](const TrafficRecord &tr1, const TrafficRecord& tr2){
        switch (column) {
            case (int)TrafficRecordModel::RecordNo: {
                if (order == Qt::AscendingOrder) {
                    if (tr1.getRecordNo() > tr2.getRecordNo()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (tr2.getRecordNo() < tr2.getRecordNo()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)TrafficRecordModel::DeviceCode: {
                if (order == Qt::AscendingOrder) {
                    if (tr1.getDeviceCode() > tr2.getDeviceCode()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (tr1.getDeviceCode() < tr2.getDeviceCode()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)TrafficRecordModel::PoleCode: {
                if (order == Qt::AscendingOrder) {
                    if (tr1.getPoleCode() > tr2.getPoleCode()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (tr1.getPoleCode() < tr2.getPoleCode()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)TrafficRecordModel::VehicleRegistrationNo: {
                if (order == Qt::AscendingOrder) {
                    if (tr1.getVehicleRegistrationNo() > tr2.getVehicleRegistrationNo()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (tr1.getVehicleRegistrationNo() < tr2.getVehicleRegistrationNo()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)TrafficRecordModel::VehicleSpeed: {
                if (order == Qt::AscendingOrder) {
                    if (tr1.getSpeed() > tr2.getSpeed()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (tr1.getSpeed() < tr2.getSpeed()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)TrafficRecordModel::RecordTime: {
                if (order == Qt::AscendingOrder) {
                    if (tr1.getRecordTime() > tr2.getRecordTime()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (tr1.getRecordTime() < tr2.getRecordTime()) {
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

void TrafficRecordModel::setupModel()
{
    TrafficRecord record1((char*)"003Traf", (char*)"K31+950");
    record1.setRegistrationNo((char*)"BYZ858");
    record1.setSpeed(4321);
    this->m_trafficRecordData.append(record1);
}

void TrafficRecordModel::appendRow(TrafficRecord newRow, const QModelIndex &parent)
{
    int row = this->rowCount();
    beginInsertRows(parent, row, row);
    this->m_trafficRecordData.append(newRow);
    endInsertRows();
}

void TrafficRecordModel::removeRow(int row, const QModelIndex &parent)
{
    if (row < 0 || row > this->m_trafficRecordData.size()) {
        qDebug() << "Invalid Index";
    } else {
        beginRemoveRows(parent, row, row);
        this->m_trafficRecordData.erase(this->m_trafficRecordData.begin() + row);
        endRemoveRows();
    }
}

int TrafficRecordModel::findRecord_getIndex(QString recordNo)
{
    for (int i = 0; i < this->m_trafficRecordData.size(); i++) {
        if (this->m_trafficRecordData.at(i).getRecordNo() == recordNo) return i;
    }
    return -1;
}

QVector<TrafficRecord> TrafficRecordModel::getRecordData()
{
    QVector<TrafficRecord> record = this->m_trafficRecordData;
    return record;
}

QVector<QCPGraphData> TrafficRecordModel::getTimeData(QDateTime start, QDateTime end, double interval, QString poleCode
                                                      , int &Max)
{
    if(start>end)return QVector<QCPGraphData>();
    int number= start.secsTo(end) / 60;
    QVector<QCPGraphData> timeData(number);
    QVector<QDateTime> recData;

    QDateTime now=start;
    for(int i=0;i<number;i++)
    {
        timeData[i].key=now.toMSecsSinceEpoch()/1000.0;
        timeData[i].value=0;
        now=now.addSecs(60 * interval);
    }

    for (int i = 0; i < this->m_trafficRecordData.size(); i++) {
        QDateTime rec = this->m_trafficRecordData.at(i).getRecordTime();
        QDateTime recTime = this->m_trafficRecordData.at(i).getRecordTime();
        QString recPole = this->m_trafficRecordData.at(i).getPoleCode();
        if (poleCode == "" || recPole == poleCode) {
            if (recTime >= start && recTime <= end) {
                recData.append(rec);
            }
        }
    }
    if (recData.size() <= 0) {
        qDebug() << "Cannot find data" << recData.size();
        return timeData;
    }
    Max=0;
    int curnumber=0;
    for(int i=0;i<recData.size();i++)
    {
        curnumber=start.secsTo(recData[i])/60/interval;
        int val = timeData[curnumber].value++;
        Max=std::max(Max, val);
    }

    return timeData;
}

int TrafficRecordModel::totalRecords()
{
    return this->m_trafficRecordData.size();
}

