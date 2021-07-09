#ifndef WHEREAREYOUWIDGET_H
#define WHEREAREYOUWIDGET_H

#include <QWidget>
#include "cellularrecordmodel.h"
#include "cctvrecordmodel.h"
#include "trafficrecordmodel.h"
#include "polemodel.h"
#include "monitormodel.h"
#include "locationfilterproxymodel.h"

namespace Ui {
class WhereAreYouWidget;
}

class WhereAreYouWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WhereAreYouWidget(QWidget *parent = nullptr);
    ~WhereAreYouWidget();

    void initialise(PoleModel *poleModel, MonitorModel *monitorModel, CCTVRecordModel *cctvRecordModel,
                    TrafficRecordModel *trafficRecordModel, CellularRecordModel *cellularRecordModel);

private:
    void init();


private:
    Ui::WhereAreYouWidget *ui;

    QString poleCode;
    LocationFilterProxyModel *locationFilterProxyModel;

    PoleModel *poleModel;
    MonitorModel *monitorModel;
    CCTVRecordModel *cctvRecordModel;
    TrafficRecordModel *trafficRecordModel;
    CellularRecordModel *cellularRecordModel;

};

#endif // WHEREAREYOUWIDGET_H
