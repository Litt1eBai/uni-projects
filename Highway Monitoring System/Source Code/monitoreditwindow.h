#ifndef MONITOREDITWINDOW_H
#define MONITOREDITWINDOW_H

#include "monitor.h"
#include "monitormodel.h"
#include "polemodel.h"
#include <QDataWidgetMapper>
#include <QDialog>

namespace Ui {
class MonitorEditWindow;
}

class MonitorEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MonitorEditWindow(QWidget *parent = nullptr);
    explicit MonitorEditWindow(PoleModel *poleModel, MonitorModel *monitorModel, QWidget *parent = nullptr);
    ~MonitorEditWindow();

public slots:
    void getMonitorModel(MonitorModel *model);
    void setMonitorModelIndex(const QModelIndex &index);
    void setPassedMonitorData(Monitor currentData);

private:
    void init();

signals:
    void updatedMonitorData(Monitor data);
    void updateMonitorDataToModel(Monitor data, QModelIndex &currentIndex);

private:
    Ui::MonitorEditWindow *ui;

    // models
    MonitorModel *monitorModel;
    PoleModel *poleModel;

    // Data
    QModelIndex m_currentMonitorModelIndex;
    Monitor m_currentMonitorData;

    // Got index
    bool m_gotMonitorModelIndexFlag;

    // event
    void closeEvent(QCloseEvent *event);

};

#endif // MONITOREDITWINDOW_H
