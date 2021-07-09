#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include "polemodel.h"
#include "monitormodel.h"
#include "cellularrecordmodel.h"
#include "cctvrecordmodel.h"
#include "trafficrecordmodel.h"
#include <QWidget>

namespace Ui {
class StatisticsWidget;
}

class StatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    void initialise(PoleModel* poleModel, MonitorModel *monitorModel, CellularRecordModel *cellularRecordModel,
                    CCTVRecordModel *CCTVRecordModel, TrafficRecordModel *trafficRecordModel);
    ~StatisticsWidget();

private:
    void init();

private:
    Ui::StatisticsWidget *ui;

    // model pointers
    PoleModel *poleModel;
    MonitorModel *monitorModel;
    CellularRecordModel *cellularRecordModel;
    CCTVRecordModel *cctvRecordModel;
    TrafficRecordModel *trafficRecordModel;

};

#endif // STATISTICSWIDGET_H
