#ifndef MONITORTABLEVIEWWIDGET_H
#define MONITORTABLEVIEWWIDGET_H

#include "monitormodel.h"
#include "monitoreditwindow.h"
#include "polemodel.h"
#include <QWidget>

namespace Ui {
class MonitorTableViewWidget;
}

class MonitorTableViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonitorTableViewWidget(QWidget *parent = nullptr);
    explicit MonitorTableViewWidget(PoleModel *poleModel, MonitorModel *monitorModel, QWidget *parent = nullptr);
    ~MonitorTableViewWidget();

signals:
    void sendMonitorModel(MonitorModel *model);
    void sendMonitorIndex(const QModelIndex &index);
    void updatedMonitorData(Monitor updatedData, const QModelIndex &indexOfData);
    void sendMonitorData(Monitor currentData);

public slots:
    void setMonitorModel(MonitorModel *monitorModel);
    void setPoleModel(PoleModel *poleModel);
    void initialise(PoleModel *poleModel, MonitorModel *monitorModel);

private:
    void init();

private:
    Ui::MonitorTableViewWidget *ui;

    MonitorModel *monitorModel;
    PoleModel *poleModel;

    MonitorEditWindow* monitorEdit;
};

#endif // MONITORTABLEVIEWWIDGET_H
