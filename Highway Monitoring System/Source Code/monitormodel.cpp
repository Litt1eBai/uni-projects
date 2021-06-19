#include "monitormodel.h"
#include <QDebug>

MonitorModel::MonitorModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    setupModel();
}

QVariant MonitorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
            case MonitorModel::DeviceCode: return QString("Device Code");
            case MonitorModel::DeviceType: return QString("Device Type");
            case MonitorModel::WorkStatus: return QString("Work Status");
            case MonitorModel::Description: return QString("Description");
            case MonitorModel::InstallationDate: return QString("Date of Installation");
        }
    } else {
        return QStringLiteral("%1").arg(section);
    }
    return QVariant();
}

int MonitorModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->m_monitorData.size();
}

int MonitorModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return 5;
}

QVariant MonitorModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole: {
            switch (index.column()) {
                case MonitorModel::DeviceCode: return m_monitorData.at(index.row()).getDeviceCode();
                case MonitorModel::DeviceType: {
                    MonitorDeviceType type = m_monitorData.at(index.row()).getDeviceType();
                    if (type == MonitorDeviceType::CCTV) {
                        return QString("CCTV");
                    } else if (type == MonitorDeviceType::Cellular) {
                        return QString("Cellular Monitor");
                    } else if (type == MonitorDeviceType::TrafficFlow) {
                        return QString("Traffic Monitor");
                    } else if (type == MonitorDeviceType::Abstract) {
                        return QString("Not Defined");
                    } else {
                        return QString("Error");
                    }
                }
                case MonitorModel::WorkStatus: {
                    DeviceWorkStatus workStatus = m_monitorData.at(index.row()).getWorkStatus();
                    if (workStatus == DeviceWorkStatus::Running) {
                        return QString("Running");
                    } else if (workStatus == DeviceWorkStatus::Down) {
                        return QString("Down");
                    } else if (workStatus == DeviceWorkStatus::NotInstalled) {
                        return QString("Not Installed");
                    } else {
                        return QString("No Status");
                    }
                }
                case MonitorModel::Description: return m_monitorData.at(index.row()).getDescription();
                case MonitorModel::InstallationDate: return m_monitorData.at(index.row()).getInstallationDate().toString();
            }
        }
    }

    return QVariant();
}

bool MonitorModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        if (role == Qt::EditRole) {
            if (!checkIndex(index))
                return false;

            // Save value from editor
            switch (index.column()) {
                case MonitorModel::DeviceCode: {
                    QString val = value.toString();
                    if (val.size() > 11)
                        qDebug() << "Error";
                    m_monitorData[index.row()].setDeviceCode((char*)val.toStdString().c_str());
                    break;
                }
                case MonitorModel::DeviceType: {
                    m_monitorData[index.row()].setDeviceType((MonitorDeviceType)value.toInt());
                    break;
                }
                case MonitorModel::WorkStatus: {
                    m_monitorData[index.row()].setDeviceWorkStatus((DeviceWorkStatus)value.toInt());
                    break;
                }
                case MonitorModel::Description: {
                    QString val = value.toString();
                    if (val.size() > 100)
                        qDebug() << "Error";
                    m_monitorData[index.row()].setDescription((char*)val.toStdString().c_str());
                    break;
                }
                case MonitorModel::InstallationDate: {
                    m_monitorData[index.row()].setInstallationTime(value.toDateTime());
                    break;
                }
            }
        }
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags MonitorModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

void MonitorModel::appedRow(Monitor newRow, const QModelIndex &parent)
{
    int row = this->rowCount();
    qDebug() << "before" << this->m_monitorData.size();
    beginInsertRows(parent, row, row);
    this->m_monitorData.push_back(newRow);
    qDebug() << "after" << this->m_monitorData.size();
    endInsertRows();
}

void MonitorModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    if (row < 0 || row > this->m_monitorData.size()) {
        qDebug() << "Invalid Index";
    } else {
        this->m_monitorData.erase(this->m_monitorData.begin() + row);
    }
    endRemoveRows();
}

bool MonitorModel::findMonitor(QString monitorCode)
{
    for (int i = 0; i < this->m_monitorData.size(); i++) {
        if (this->m_monitorData.at(i).getDeviceCode() == monitorCode) return true;
    }
    return false;
}

Monitor MonitorModel::findMonitor_getData(QString monitorCode)
{
    for (int i = 0; i < this->m_monitorData.size(); i++) {
        if (this->m_monitorData.at(i).getDeviceCode() == monitorCode) return m_monitorData.at(i);
    }
}

Monitor MonitorModel::findMonitor_getData(MonitorDeviceType type, QString monitorCode)
{
    for (int i = 0; i < this->m_monitorData.size(); i++) {
        if (this->m_monitorData.at(i).getDeviceCode() == monitorCode &&
                this->m_monitorData.at(i).getDeviceType() == type) return m_monitorData.at(i);
    }
}

int MonitorModel::findMonitor_getIndex(QString monitorCode)
{
    for (int i = 0; i < this->m_monitorData.size(); i++) {
        if (this->m_monitorData.at(i).getDeviceCode() == monitorCode) return i;
    }
    return -1;
}

int MonitorModel::findMonitor_getIndex(MonitorDeviceType type, QString monitorCode)
{
    for (int i = 0; i < this->m_monitorData.size(); i++) {
        if (this->m_monitorData.at(i).getDeviceCode() == monitorCode &&
                this->m_monitorData.at(i).getDeviceType() == type) return i;
    }
    return -1;
}

Monitor MonitorModel::getCurrentData(const QModelIndex &index) const
{
    return m_monitorData.at(index.row());
}

void MonitorModel::sort(int column, Qt::SortOrder order)
{
    beginResetModel();

    std::sort(this->m_monitorData.begin(), this->m_monitorData.end(),
          [=](const Monitor &m1, const Monitor& m2){
        switch (column) {
            case (int)MonitorModel::DeviceCode: {
                if (order == Qt::AscendingOrder) {
                    if (m1.getDeviceCode() > m2.getDeviceCode()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (m1.getDeviceCode() < m2.getDeviceCode()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)MonitorModel::DeviceType: {
                return false;
                break;
            }
            case (int)MonitorModel::WorkStatus: {
                return false;
                break;
            }
            case (int)MonitorModel::Description: {
                if (order == Qt::AscendingOrder) {
                    if (m1.getDescription() > m2.getDescription()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (m1.getDescription() < m2.getDescription()) {
                        return true;
                    } else {
                        return false;
                    }
                }
                break;
            }
            case (int)MonitorModel::InstallationDate: {
                if (order == Qt::AscendingOrder) {
                    if (m1.getInstallationDate() > m2.getInstallationDate()) {
                        return true;
                    } else {
                        return false;
                    }
                } else if (order == Qt::DescendingOrder) {
                    if (m1.getInstallationDate() < m2.getInstallationDate()) {
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

void MonitorModel::updateCurrentData(Monitor updatedData, int index)
{
    if (index >= 0 && index < this->m_monitorData.size()) {
        this->m_monitorData[index] = updatedData;
    } else {
        qDebug() << "Data update failed";
    }
}

void MonitorModel::setUpdatedData(Monitor updatedData, const QModelIndex &indexOfData)
{
    qDebug() << "update model called";
    qDebug() << indexOfData.row();
    qDebug() << "MaxIndex" << (this->m_monitorData.size() - 1) << ", Index" << indexOfData.row();
    qDebug() << "------------------------------------";

    if (indexOfData.row() >= this->m_monitorData.size()) {
        qDebug() << "Size too big" << (this->m_monitorData.size() - 1) << " < " << indexOfData.row();
        qDebug() << "------------------------------------";
        qDebug() << "";
        return;
    }
    if (this->m_monitorData[indexOfData.row()].getDeviceCode() != updatedData.getDeviceCode()) {
        char *newDeviceCode = new char[10];
        updatedData.getDeviceCode(newDeviceCode);
        m_monitorData[indexOfData.row()].setDeviceCode(newDeviceCode);
    }
    if (this->m_monitorData[indexOfData.row()].getDescription() != updatedData.getDescription()) {
        char *newDescription = new char[100];
        updatedData.getDescription(newDescription);
        m_monitorData[indexOfData.row()].setDescription(newDescription);
    }
    if (this->m_monitorData[indexOfData.row()].getInstallationDate() != updatedData.getInstallationDate()) {
        m_monitorData[indexOfData.row()].setInstallationTime(updatedData.getInstallationDate());
    }
    if (this->m_monitorData[indexOfData.row()].getDeviceType() != updatedData.getDeviceType()) {
        m_monitorData[indexOfData.row()].setDeviceType(updatedData.getDeviceType());
    }
    if (this->m_monitorData[indexOfData.row()].getWorkStatus() != updatedData.getWorkStatus()) {
        m_monitorData[indexOfData.row()].setDeviceWorkStatus(updatedData.getWorkStatus());
    }
    emit dataChanged(indexOfData, indexOfData, QVector<int>() << Qt::EditRole);

}

void MonitorModel::setupModel()
{
    Monitor monitor1;
    monitor1.setDevice(MonitorDeviceType::CCTV, "001CCTV");
    monitor1.setDeviceWorkStatus(DeviceWorkStatus::Running);
    monitor1.setDescription("Monitor at Service Centre Right");
    this->m_monitorData.push_back(monitor1);

    Monitor monitor2;
    monitor2.setDevice(MonitorDeviceType::Cellular, "001Cel");
    monitor2.setDeviceWorkStatus(DeviceWorkStatus::Running);
    monitor2.setDescription("Monitor at Service Centre Right");
    this->m_monitorData.push_back(monitor2);

    Monitor monitor3;
    monitor3.setDevice(MonitorDeviceType::TrafficFlow, "001Traf");
    monitor3.setDeviceWorkStatus(DeviceWorkStatus::Running);
    monitor3.setDescription("Monitor at Service Centre Right");
    this->m_monitorData.push_back(monitor3);


    Monitor monitor4;
    monitor4.setDevice(MonitorDeviceType::CCTV, "002CCTV");
    monitor4.setDeviceWorkStatus(DeviceWorkStatus::Running);
    monitor4.setDescription("Monitor at Interchange1");
    this->m_monitorData.push_back(monitor4);

    Monitor monitor5;
    monitor5.setDevice(MonitorDeviceType::Cellular, "002Cel");
    monitor5.setDeviceWorkStatus(DeviceWorkStatus::Running);
    monitor5.setDescription("Monitor at Interchange1");
    this->m_monitorData.push_back(monitor5);

    Monitor monitor6;
    monitor6.setDevice(MonitorDeviceType::TrafficFlow, "002Traf");
    monitor6.setDeviceWorkStatus(DeviceWorkStatus::Running);
    monitor6.setDescription("Monitor at Interchange1");
    this->m_monitorData.push_back(monitor6);

    Monitor monitor7;
    monitor7.setDevice(MonitorDeviceType::CCTV, "003CCTV");
    monitor7.setDeviceWorkStatus(DeviceWorkStatus::Running);
    monitor7.setDescription("Monitor at Interchange2");
    this->m_monitorData.push_back(monitor7);

    Monitor monitor8;
    monitor8.setDevice(MonitorDeviceType::Cellular, "003Cel");
    monitor8.setDeviceWorkStatus(DeviceWorkStatus::Running);
    monitor8.setDescription("Monitor at Interchange2");
    this->m_monitorData.push_back(monitor8);

    Monitor monitor9;
    monitor9.setDevice(MonitorDeviceType::TrafficFlow, "003Traf");
    monitor9.setDeviceWorkStatus(DeviceWorkStatus::Running);
    monitor9.setDescription("Monitor at Interchange2");
    this->m_monitorData.push_back(monitor9);


}
