#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include "polemodel.h"
#include "monitormodel.h"
#include <QWidget>

namespace Ui {
class StatisticsWidget;
}

class StatisticsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    void initialise(PoleModel* poleModel, MonitorModel *monitorModel);
    ~StatisticsWidget();

private:
    void init();

private:
    Ui::StatisticsWidget *ui;

    // model pointers
    PoleModel *poleModel;
    MonitorModel *monitorModel;

};

#endif // STATISTICSWIDGET_H
