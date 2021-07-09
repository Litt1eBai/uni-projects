#include "polemodel.h"
#include <QFont>
#include <QDebug>
#include <QIcon>
#include <fstream>
#include <QDir>

PoleModel::PoleModel(QObject *parent)
    : QAbstractTableModel(parent)
{
//    loadDataFromFile();
    setupModel();
}

QVariant PoleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DecorationRole) {
        switch (section) {
            case PoleModel::CCTVInstall: return QIcon(":/Icons/MonitorType/CCTV");
            case PoleModel::CellularMonitorInstall: return QIcon(":/Icons/MonitorType/Cellular");
            case PoleModel::TrafficMinitorInstall: return QIcon(":/Icons/MonitorType/Traffic");
        }
    }
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case PoleModel::PoleCode: return QString("Pole Code");
        case PoleModel::Longitude: return QString("Longitude");
        case PoleModel::Latitude: return QString("Latitude");
        case PoleModel::Description: return QString("Description");
        case PoleModel::CCTVInstall: return QString("CCTV Device");
        case PoleModel::CellularMonitorInstall: return QString("Cellular Monitor");
        case PoleModel::TrafficMinitorInstall: return QString("Traffic Monitor");
        }
    } else {
        return QStringLiteral("%1").arg(section);
    }
    return QVariant();
}

int PoleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->m_poleData.size();
}

int PoleModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 7;
}

QVariant PoleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole: {
            switch (index.column()) {
                case PoleModel::PoleCode: return m_poleData.at(index.row()).getPoleCode();
                case PoleModel::Longitude: return m_poleData.at(index.row()).getLongitude();
                case PoleModel::Latitude: return m_poleData.at(index.row()).getLatitude();
                case PoleModel::Description: return m_poleData.at(index.row()).getDescription();
                case PoleModel::CCTVInstall: {
                    QString CCTVDeviceCode = m_poleData.at(index.row()).getDeviceCode(MonitorDeviceType::CCTV);
                    if (CCTVDeviceCode == "") return QString("Not Installed");
                    else return CCTVDeviceCode;
                }
                case PoleModel::CellularMonitorInstall: {
                    QString cellularDeviceCode = m_poleData.at(index.row()).getDeviceCode(MonitorDeviceType::Cellular);
                    if (cellularDeviceCode == "") return QString("Not Installed");
                    else return cellularDeviceCode;
                }
                case PoleModel::TrafficMinitorInstall: {
                    QString traffDeviceCode = m_poleData.at(index.row()).getDeviceCode(MonitorDeviceType::TrafficFlow);
                    if (traffDeviceCode == "") return QString("Not Installed");
                    else return traffDeviceCode;
                }
            }
        }
        case Qt::FontRole: {
            switch (index.column()) {
                case PoleModel::PoleCode:
                case PoleModel::Longitude:
                case PoleModel::Latitude:
                case PoleModel::Description: return QFont();
                case PoleModel::CCTVInstall: {
                    QString CCTVDeviceCode = m_poleData.at(index.row()).getDeviceCode(MonitorDeviceType::CCTV);
                    if (CCTVDeviceCode == "") {
                        QFont boldFont;
                        boldFont.setBold(true);
                        return boldFont;
                    }
                    else return QFont();
                }
                case PoleModel::CellularMonitorInstall: {
                    QString cellularDeviceCode = m_poleData.at(index.row()).getDeviceCode(MonitorDeviceType::Cellular);
                    if (cellularDeviceCode == "") {
                        QFont boldFont;
                        boldFont.setBold(true);
                        return boldFont;
                    }
                    else return QFont();
                }
                case PoleModel::TrafficMinitorInstall: {
                    QString traffDeviceCode = m_poleData.at(index.row()).getDeviceCode(MonitorDeviceType::TrafficFlow);
                    if (traffDeviceCode == "") {
                        QFont boldFont;
                        boldFont.setBold(true);
                        return boldFont;
                    }
                    else return QFont();
                }
            }
        }
    }
    return QVariant();
}

bool PoleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == Qt::EditRole) {
            if (!checkIndex(index))
                return false;

            // Save value from editor
            switch (index.column()) {
                case PoleModel::PoleCode: {
                    QString val = value.toString();
                    if (val.size() > 7)
                        qDebug() << "Error";

                    m_poleData[index.row()].setPoleCode((char*)val.toStdString().c_str());
                    break;
                }
                case PoleModel::Longitude: {
                    m_poleData[index.row()].setLongitude(value.toInt());
                    break;
                }
                case PoleModel::Latitude: {
                    m_poleData[index.row()].setLatitude(value.toInt());
                    break;
                }
                case Description: {
                    QString val = value.toString();
                    if (val.size() > 199)
                        qDebug() << "Error";
                    m_poleData[index.row()].setDescription((char*)val.toStdString().c_str());
                    break;
                }
                case PoleModel::CCTVInstall: {
                    QString val = value.toString();
                    if (val.size() > 7)
                        qDebug() << "Error";
                    m_poleData[index.row()].addMonitor(MonitorDeviceType::CCTV,
                                                                  (char*)val.toStdString().c_str());
                    break;
                }
                case PoleModel::CellularMonitorInstall: {
                    QString val = value.toString();
                    if (val.size() > 7)
                        qDebug() << "Error";
                    m_poleData[index.row()].addMonitor(MonitorDeviceType::Cellular,
                                                                  (char*)val.toStdString().c_str());
                    break;
                }
                case PoleModel::TrafficMinitorInstall: {
                    QString val = value.toString();
                    if (val.size() > 7)
                        qDebug() << "Error";
                    m_poleData[index.row()].addMonitor(MonitorDeviceType::TrafficFlow,
                                                                  (char*)val.toStdString().c_str());
                    break;
                }
            }

            emit dataChanged(index, index, QVector<int>() << role);
        }
        return true;
    }
    return false;
}

Qt::ItemFlags PoleModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

Pole PoleModel::getCurrentData(const QModelIndex &index) const
{
    return m_poleData.at(index.row());
}

bool PoleModel::findPole(QString poleCode)
{
    for (int i = 0; i < this->m_poleData.size(); i++) {
        if (this->m_poleData.at(i).getPoleCode() == poleCode) return true;
    }
    return false;
}

Pole PoleModel::findPole_getData(QString poleCode)
{
    for (int i = 0; i < this->m_poleData.size(); i++) {
        if (this->m_poleData.at(i).getPoleCode() == poleCode) return this->m_poleData.at(i);
    }
}

int PoleModel::findPole_getIndex(QString poleCode)
{
    for (int i = 0; i < this->m_poleData.size(); i++) {
        if (this->m_poleData.at(i).getPoleCode() == poleCode) return i;
    }
    return -1;
}

void PoleModel::setUpdatedData(Pole updatedData, const QModelIndex &indexOfData)
{
    qDebug() << "update model called";
    qDebug() << indexOfData.row();
    qDebug() << "MaxIndex" << (this->m_poleData.size() - 1) << ", Index" << indexOfData.row();
    qDebug() << "------------------------------------";

    if (indexOfData.row() >= this->m_poleData.size()) {
        qDebug() << "Size too big" << (this->m_poleData.size() - 1) << " < " << indexOfData.row();
        qDebug() << "------------------------------------";
        qDebug() << "";
        return;
    }
    if (this->m_poleData[indexOfData.row()].getPoleCode() != updatedData.getPoleCode()) {
        char *newPoleCode = new char[8];
        updatedData.getPoleCode(newPoleCode);
        this->m_poleData[indexOfData.row()].setPoleCode(newPoleCode);
    }
    if (this->m_poleData[indexOfData.row()].getLongitude() != updatedData.getLongitude()) {
        this->m_poleData[indexOfData.row()].setLongitude(updatedData.getLongitude());
    }
    if (this->m_poleData[indexOfData.row()].getLatitude() != updatedData.getLatitude()) {
        this->m_poleData[indexOfData.row()].setLatitude(updatedData.getLatitude());
    }
    if (this->m_poleData[indexOfData.row()].getDeviceCode(MonitorDeviceType::CCTV) !=
            updatedData.getDeviceCode(MonitorDeviceType::CCTV)) {
        char *newDeviceCode = new char[10];
        updatedData.getDeviceCode(MonitorDeviceType::CCTV, newDeviceCode);
        this->m_poleData[indexOfData.row()].addMonitor(MonitorDeviceType::CCTV, newDeviceCode);
    }
    if (this->m_poleData[indexOfData.row()].getDeviceCode(MonitorDeviceType::Cellular) !=
            updatedData.getDeviceCode(MonitorDeviceType::Cellular)) {
        char *newDeviceCode = new char[10];
        updatedData.getDeviceCode(MonitorDeviceType::Cellular, newDeviceCode);
        this->m_poleData[indexOfData.row()].addMonitor(MonitorDeviceType::Cellular, newDeviceCode);
    }
    if (this->m_poleData[indexOfData.row()].getDeviceCode(MonitorDeviceType::TrafficFlow) !=
            updatedData.getDeviceCode(MonitorDeviceType::TrafficFlow)) {
        char *newDeviceCode = new char[10];
        updatedData.getDeviceCode(MonitorDeviceType::TrafficFlow, newDeviceCode);
        this->m_poleData[indexOfData.row()].addMonitor(MonitorDeviceType::TrafficFlow, newDeviceCode);
    }
    if (this->m_poleData[indexOfData.row()].getDescription() !=
            updatedData.getDescription()) {
        char *newDescription = new char[100];
        updatedData.getDescription(newDescription);
        this->m_poleData[indexOfData.row()].setDescription(newDescription);
    }
    qDebug() << "Data Changed";
    emit dataChanged(indexOfData, indexOfData, QVector<int>() << Qt::EditRole);
}


void PoleModel::sort(int column, Qt::SortOrder order)
{
    beginResetModel();

    std::sort(this->m_poleData.begin(), this->m_poleData.end(), [=](Pole p1, Pole p2){
        switch (column) {
            case (int)PoleModel::PoleCode: {
                if (order == Qt::AscendingOrder) {
                    if (p1.getPoleCode() > p2.getPoleCode()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (p1.getPoleCode() < p2.getPoleCode()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)PoleModel::Longitude: {
                if (order == Qt::AscendingOrder) {
                    if (p1.getLongitude() > p2.getLongitude()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (p1.getLongitude() < p2.getLongitude()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)PoleModel::Latitude: {
                if (order == Qt::AscendingOrder) {
                    if (p1.getLatitude() > p2.getLatitude()) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (p1.getLatitude() < p2.getLatitude()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)PoleModel::Description: {
                if (order == Qt::AscendingOrder) {
                    if (p1.getDescription() > p2.getDescription()) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (p1.getDescription() < p2.getDescription()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)PoleModel::CCTVInstall: {
                if (order == Qt::AscendingOrder) {
                    if (p1.getDeviceCode(MonitorDeviceType::CCTV) > p2.getDeviceCode(MonitorDeviceType::CCTV)) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (p1.getDeviceCode(MonitorDeviceType::CCTV) < p2.getDeviceCode(MonitorDeviceType::CCTV)) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)PoleModel::CellularMonitorInstall: {
                if (order == Qt::AscendingOrder) {
                    if (p1.getDeviceCode(MonitorDeviceType::Cellular) > p2.getDeviceCode(MonitorDeviceType::Cellular)) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (p1.getDeviceCode(MonitorDeviceType::Cellular) < p2.getDeviceCode(MonitorDeviceType::Cellular)) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)PoleModel::TrafficMinitorInstall: {
                if (order == Qt::AscendingOrder) {
                    if (p1.getDeviceCode(MonitorDeviceType::TrafficFlow) > p2.getDeviceCode(MonitorDeviceType::TrafficFlow)) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (p1.getDeviceCode(MonitorDeviceType::TrafficFlow) < p2.getDeviceCode(MonitorDeviceType::TrafficFlow)) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            default:
                return false;
        }
        // in case
        return false;
    });

    endResetModel();
}

//void PoleModel::loadDataFromFile()
//{
//    std::fstream poleDataFile;
//    poleDataFile.open(poleData_filePath.toStdString(), std::ios::binary | std::ios::in);

//}

void PoleModel::appedRow(Pole newRow, const QModelIndex &parent)
{
    int row = this->rowCount();
    beginInsertRows(parent, row, row);
    this->m_poleData.push_back(newRow);
    endInsertRows();
}

void PoleModel::removeRow(int row, const QModelIndex &parent)
{
    if (row < 0 || row > this->m_poleData.size()) {
        qDebug() << "Invalid Index";
    } else {
        beginRemoveRows(parent, row, row);
        this->m_poleData.erase(this->m_poleData.begin() + row);
        endRemoveRows();
    }
}


void PoleModel::setupModel()
{
    Pole pole1(102.214814, 24.704153);
    pole1.setPoleCode((char*)"K96+430");
    pole1.addMonitor(MonitorDeviceType::CCTV, (char*)"001CCTV");
    pole1.addMonitor(MonitorDeviceType::Cellular, (char*)"001Cel");
    pole1.addMonitor(MonitorDeviceType::TrafficFlow, (char*)"001Traf");
    pole1.setDescription((char*)"Service Centre Right");
    this->m_poleData.push_back(pole1);

    Pole pole2(120.057727, 32.156814 );
    pole2.setPoleCode((char*)"K56+400");
    pole2.addMonitor(MonitorDeviceType::CCTV, (char*)"002CCTV");
    pole2.addMonitor(MonitorDeviceType::Cellular, (char*)"002Cel");
    pole2.addMonitor(MonitorDeviceType::TrafficFlow, (char*)"002Traf");
    pole2.setDescription((char*)"Interchange1");
    this->m_poleData.push_back(pole2);

    Pole pole3(104.114286, 30.698975);
    pole3.setPoleCode((char*)"K31+950");
    pole3.addMonitor(MonitorDeviceType::CCTV, (char*)"003CCTV");
    pole3.addMonitor(MonitorDeviceType::Cellular, (char*)"003Cel");
    pole3.addMonitor(MonitorDeviceType::TrafficFlow, (char*)"003Traf");
    pole3.setDescription((char*)"Interchange2");
    this->m_poleData.push_back(pole3);

}
