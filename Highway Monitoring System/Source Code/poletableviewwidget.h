#ifndef POLETABLEVIEWWIDGET_H
#define POLETABLEVIEWWIDGET_H

#include "polemodel.h"
#include "monitormodel.h"
#include "poleeditwindow.h"
#include <QWidget>

namespace Ui {
class PoleTableViewWidget;
}

class PoleTableViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PoleTableViewWidget(QWidget *parent = nullptr);
    explicit PoleTableViewWidget(PoleModel *poleModel, MonitorModel *monitorModel, QWidget *parent = nullptr);
    ~PoleTableViewWidget();

signals:
    void sendPoleModel(PoleModel *model);
    void sendPoleModelIndex(const QModelIndex &index);
    void updatedPoleData(Pole updatedData, const QModelIndex &indexOfData);
    void sendPoleData(Pole currentData);
    void sendSelectedDeviceCode(QString deviceCode);
    void sendMonitorInfo(MonitorDeviceType type, QString deviceCode);

public slots:
    void setPoleModel(PoleModel *poleModel);
    void setMonitorModel(MonitorModel *monitorModel);
    void initialise(PoleModel *poleModel, MonitorModel *monitorModel);

private:
    void init();

private:
    Ui::PoleTableViewWidget *ui;

private:
    // pointers to models
    PoleModel *poleModel;
    MonitorModel *monitorModel;

    // pole edit window
    PoleEditWindow *poleEdit;
};

#endif // POLETABLEVIEWWIDGET_H
