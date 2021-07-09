#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include "polemodel.h"
#include "monitormodel.h"
#include "trafficrecordmodel.h"
#include "cellularrecordmodel.h"
#include "cctvrecordmodel.h"
#include "locationfilterproxymodel.h"


namespace Ui {
class DashboardWidget;
}

class DashboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget *parent = nullptr);
    ~DashboardWidget();

    void initialise(PoleModel *poleModel, MonitorModel *monitorModel, CCTVRecordModel *cctvRecordModel,
                    TrafficRecordModel *trafficRecordModel, CellularRecordModel *cellularRecordModel);

private:
    void init();

private:
    Ui::DashboardWidget *ui;

    QString poleCode;
    LocationFilterProxyModel *locationFilterProxyModel;

    PoleModel *poleModel;
    MonitorModel *monitorModel;
    CCTVRecordModel *cctvRecordModel;
    TrafficRecordModel *trafficRecordModel;
    CellularRecordModel *cellularRecordModel;


};

#endif // DASHBOARDWIDGET_H
