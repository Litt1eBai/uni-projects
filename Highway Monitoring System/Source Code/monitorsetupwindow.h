#ifndef MONITORSETUPWINDOW_H
#define MONITORSETUPWINDOW_H

#include "monitor.h"
#include "monitormodel.h"
#include "pole.h"
#include "polemodel.h"
#include <QDialog>

namespace Ui {
class MonitorSetupWindow;
}

class MonitorSetupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MonitorSetupWindow(QWidget *parent = nullptr);
    explicit MonitorSetupWindow(PoleModel *poleMode, MonitorModel *monitorModel, QWidget *parent = nullptr);
    ~MonitorSetupWindow();

private:
    void init();


signals:
    void sendNewMonitorData(Monitor newMonitorData);

public slots:
    void setPoleModel(PoleModel *poleModel);
    void setMonitorModel(MonitorModel *monitorModel);

private:
    Ui::MonitorSetupWindow *ui;

private:
    // data
    Monitor m_monitorData;

private:
    // model pointers
    PoleModel *poleModel;
    MonitorModel *monitorModel;

};

#endif // MONITORSETUPWINDOW_H
