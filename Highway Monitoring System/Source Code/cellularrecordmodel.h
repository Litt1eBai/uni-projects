#ifndef CELLULARRECORDMODEL_H
#define CELLULARRECORDMODEL_H

#include <QAbstractTableModel>
#include "cellularrecord.h"

class CellularRecordModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CellularRecordModel(QObject *parent = nullptr);

    // Header:
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


public:
    // custom
    enum { RecordNo = 0, DeviceCode, PoleCode, IMEI, RecordTime };

    void appendRow(CellularRecord newRow, const QModelIndex &parent = QModelIndex());
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    CellularRecord getCurrentData(const QModelIndex &index) const;
    int getNextRecordNo();

    bool findRecord_recordNo(QString recordNo);
    CellularRecord findRecord_getSingleRecord(QString recordNo);
    int findRecord_getIndex(QString recordNo);
    QVector<CellularRecord> findRecord_getRecords_poleCode(QString poleCode);
    QVector<CellularRecord> findRecord_getRecords_deviceCode(QString deviceCode);

public slots:
    void setUpdatedData(CellularRecord updatedData, const QModelIndex &indexOfData);

private:
    QVector<CellularRecord> m_cellularRecordData;



private:
};

#endif // CELLULARRECORDMODEL_H
