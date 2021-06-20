#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include "polemodel.h"
#include "monitormodel.h"
#include "cellularrecordmodel.h"
#include <QWidget>

namespace Ui {
class StatisticsWidget;
}

class StatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    void initialise(PoleModel* poleModel, MonitorModel *monitorModel, CellularRecordModel *cellularModelRecord);
    ~StatisticsWidget();

private:
    void init();

private:
    Ui::StatisticsWidget *ui;

    // model pointers
    PoleModel *poleModel;
    MonitorModel *monitorModel;
    CellularRecordModel *cellularRecordModel;

};

#endif // STATISTICSWIDGET_H
