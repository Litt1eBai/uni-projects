#ifndef CCTVRECORDPROXYMODEL_H
#define CCTVRECORDPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QDateTime>
#include <QString>


class CCTVRecordProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit CCTVRecordProxyModel(QObject *parent = nullptr);

    void setPoleCode(QString poleCode);
    void setInterval(QDateTime start, QDateTime end);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    bool filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const override;

private:
    QDateTime start;
    QDateTime end;
    QString poleCode;
};

#endif // CCTVRECORDPROXYMODEL_H
