#ifndef POLEMODEL_H
#define POLEMODEL_H

#include <QAbstractTableModel>
#include "pole.h"

class PoleModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PoleModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;


private:
    void setupModel();


public:
    // custom
    enum { PoleCode = 0, Longitude, Latitude, Description, CCTVInstall, CellularMonitorInstall, TrafficMinitorInstall };

    void appedRow(Pole newRow, const QModelIndex &parent = QModelIndex());
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    Pole getCurrentData(const QModelIndex &index) const;

    bool findPole(QString poleCode);
    Pole findPole_getData(QString poleCode);
    int findPole_getIndex(QString poleCode);

signals:
    void sendMonitorInfo(MonitorDeviceType type, QString deviceCode);

public slots:
    void setUpdatedData(Pole updatedData, const QModelIndex &indexOfData);


private:
    QVector<Pole> m_poleData;
};

#endif // POLEMODEL_H
