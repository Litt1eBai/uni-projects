//#ifndef TRAFFICRECORDMODEL_H
//#define TRAFFICRECORDMODEL_H

//#include "trafficrecord.h"
//#include <QAbstractItemModel>

//class TrafficRecordModel : public QAbstractItemModel
//{
//    Q_OBJECT

//public:
//    explicit TrafficRecordModel(QObject *parent = nullptr);

//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
//    bool setData(const QModelIndex &index, const QVariant &value,
//                 int role = Qt::EditRole) override;
//    Qt::ItemFlags flags(const QModelIndex& index) const override;
//    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

//private:
//    void setupModel();

//public:
//    enum { RecordNo = 0, DeviceCode, PoleCode, VehicleColour, VehicleRegion,
//           VehicleRegistrationNo, VehicleRegistrationType, VehicleSpeed, RecordTime};

//    void appendRow(TrafficRecord newRow, const QModelIndex &parent = QModelIndex());
//    void removeRow(int row, const QModelIndex &parent = QModelIndex());

//    int findRecord_getIndex(QString recordNo);

//public slots:
//    void setUpdatedData(TrafficRecord updatedData, const QModelIndex &indexOfData);

//private:
//    QVector<TrafficRecord> m_trafficRecordData;

//};

//#endif // TRAFFICRECORDMODEL_H
