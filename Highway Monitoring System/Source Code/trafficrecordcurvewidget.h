#ifndef TRAFFICRECORDCURVEWIDGET_H
#define TRAFFICRECORDCURVEWIDGET_H

#include "trafficrecordmodel.h"
#include "trafficrecordproxymodel.h"
#include <QWidget>

namespace Ui {
class TrafficRecordCurveWidget;
}

class TrafficRecordCurveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TrafficRecordCurveWidget(QWidget *parent = nullptr);
    ~TrafficRecordCurveWidget();

    void initialise(TrafficRecordModel *cellularRecordModel);
    void setPoleCode(QString poleCode);

private:
    void init();
    void plotSetup();
    void replot();

private:
    Ui::TrafficRecordCurveWidget *ui;

    TrafficRecordModel *trafficRecordModel;
    TrafficRecordProxyModel *trafficRecordProxyModel;
    QString m_poleCode;
    QDateTime m_start;
    QDateTime m_end;
    double m_interval;



};

#endif // TRAFFICRECORDCURVEWIDGET_H
