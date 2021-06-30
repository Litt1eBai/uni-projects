#ifndef MONITORMODEL_H
#define MONITORMODEL_H

#include "monitor.h"
#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QString>
#include <QVector>

class MonitorModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    // override
    explicit MonitorModel(QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

public:
    // custom
    enum { DeviceCode = 0, DeviceType, WorkStatus, Description, InstallationDate };

    void appedRow(Monitor newRow, const QModelIndex &parent = QModelIndex());
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    bool findMonitor(QString monitorCode);
    Monitor findMonitor_getData(QString monitorCode);
    Monitor findMonitor_getData(MonitorDeviceType type,QString monitorCode);
    int findMonitor_getIndex(QString monitorCode);
    int findMonitor_getIndex(MonitorDeviceType type, QString monitorCode);
    Monitor getCurrentData(const QModelIndex &index) const;


    void updateCurrentData(Monitor updatedData, int index);


    void setupModel();

public slots:
    void setUpdatedData(Monitor updatedData, const QModelIndex &indexOfData);


private:
    QVector<Monitor> m_monitorData;
};

#endif // MONITORMODEL_H
