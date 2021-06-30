//#include "trafficrecordmodel.h"

//TrafficRecordModel::TrafficRecordModel(QObject *parent)
//    : QAbstractItemModel(parent)
//{
//}

//QVariant TrafficRecordModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    if (role != Qt::DisplayRole)
//        return QVariant();

//    if (orientation == Qt::Horizontal) {
//        switch (section) {
//            case TrafficRecordModel::RecordNo: return QString("Record #");
//            case TrafficRecordModel::DeviceCode: return QString("Device Code");
//            case TrafficRecordModel::PoleCode: return QString("Pole Code");
//            case TrafficRecordModel::VehicleColour: return QString("Colour");
//            case TrafficRecordModel::VehicleRegion: return QString("Region");
//            case TrafficRecordModel::VehicleRegistrationNo: return QString("Registration No");
//            case TrafficRecordModel::VehicleRegistrationType: return QString("Registration Type");
//            case TrafficRecordModel::VehicleSpeed: return QString("Speed");
//        }
//    } else {
//        return QStringLiteral("%1").arg(section);
//    }
//    return QVariant();
//}

//int TrafficRecordModel::rowCount(const QModelIndex &parent) const
//{
//    if (parent.isValid())
//        return 0;

//    return this->m_trafficRecordData.size();
//}

//int TrafficRecordModel::columnCount(const QModelIndex &parent) const
//{
//    if (!parent.isValid())
//        return 0;

//    return 7;
//}

//QVariant TrafficRecordModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    switch (role) {

//        case Qt::DisplayRole: {
//            switch (index.column()) {
//                case TrafficRecordModel::RecordNo: return this->m_trafficRecordData.at(index.row()).getRecordNo();
//                case TrafficRecordModel::DeviceCode: return this->m_trafficRecordData.at(index.row()).getDeviceCode();
//                case TrafficRecordModel::PoleCode: return this->m_trafficRecordData.at(index.row()).getPoleCode();
//                case TrafficRecordModel::VehicleColour: {
//                    switch (this->m_trafficRecordData.at(index.row()).getVehicleColour()) {

//                    }
//                }
//                case TrafficRecordModel::VehicleRegion: {
//                    switch (this->m_trafficRecordData.at(index.row()).getRegistrationRegion()) {

//                    }
//                }
//                case TrafficRecordModel::VehicleRegistrationNo: {
//                    switch (this->m_trafficRecordData.at(index.row()).getRegistrationRegion()) {

//                    }
//                }
//                case TrafficRecordModel::VehicleRegistrationType: {
//                    switch (this->m_trafficRecordData.at(index.row()).getRegistrationType()) {

//                    }
//                }
//                case TrafficRecordModel::VehicleSpeed: return QVariant(this->m_trafficRecordData.at(index.column()).getSpeed()).toString();
//            }
//        }
//    }
//    return QVariant();
//}

//bool TrafficRecordModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{

//}

