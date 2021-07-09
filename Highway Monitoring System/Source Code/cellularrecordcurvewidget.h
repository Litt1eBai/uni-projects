#ifndef CELLULARRECORDCURVEWIDGET_H
#define CELLULARRECORDCURVEWIDGET_H

#include "cellularrecordmodel.h"
#include "cellularrecordproxymodel.h"
#include <QWidget>
#include <QDateTime>



namespace Ui {
class CellularRecordCurveWidget;
}

class CellularRecordCurveWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CellularRecordCurveWidget(QWidget *parent = nullptr);

    void initialise(CellularRecordModel *cellularRecordModel);
    void setPoleCode(QString poleCode);

    ~CellularRecordCurveWidget();


private:
    void init();
    void plotSetup();
    void replot();

private:
    Ui::CellularRecordCurveWidget *ui;

    CellularRecordModel *cellularRecordModel;
    CellularRecordProxyModel *cellularRecordProxyModel;
    QString m_poleCode;
    QDateTime m_start;
    QDateTime m_end;
    double m_interval;

};

#endif // CELLULARRECORDCURVEWIDGET_H
