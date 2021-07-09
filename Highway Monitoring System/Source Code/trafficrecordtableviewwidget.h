#ifndef TRAFFICRECORDTABLEVIEWWIDGET_H
#define TRAFFICRECORDTABLEVIEWWIDGET_H

#include <QWidget>
#include "trafficrecordmodel.h"

namespace Ui {
class TrafficRecordTableViewWidget;
}

class TrafficRecordTableViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrafficRecordTableViewWidget(QWidget *parent = nullptr);
    void initialise(TrafficRecordModel *trafficRecordModel);
    ~TrafficRecordTableViewWidget();

private:
    void init();

private:
    Ui::TrafficRecordTableViewWidget *ui;

    TrafficRecordModel *trafficRecordModel;

};

#endif // TRAFFICRECORDTABLEVIEWWIDGET_H
