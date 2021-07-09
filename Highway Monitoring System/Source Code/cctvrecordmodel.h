#ifndef CCTVRECORDMODEL_H
#define CCTVRECORDMODEL_H

#include "cctvrecord.h"
#include "qcustomplot.h"
#include <QVector>
#include <QAbstractTableModel>

class CCTVRecordModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CCTVRecordModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

private:
    void setupModel();

public:
    enum { RecordNo, DeviceCode, PoleCode, Description, StartTime, EndTime, FilePath };
    void appendRow(CCTVRecord newRow, const QModelIndex &parent = QModelIndex());
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

    QVector<CCTVRecord> getRecordData();
    int findRecord_getIndex(QString recordNo);
    CCTVRecord getCurrentRecord(int row);

    int totalRecords();

private:
    QVector<CCTVRecord> m_CCTVRecordData;
};

#endif // CCTVRECORDMODEL_H
