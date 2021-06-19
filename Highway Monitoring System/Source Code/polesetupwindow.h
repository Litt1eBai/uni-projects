#ifndef POLESETUPWINDOW_H
#define POLESETUPWINDOW_H

#include <QDialog>
#include "polemodel.h"
#include "monitormodel.h"
#include "pole.h"

namespace Ui {
class PoleSetupWindow;
}

class PoleSetupWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PoleSetupWindow(QDialog *parent = nullptr);
    explicit PoleSetupWindow(PoleModel *poleModel, MonitorModel* monitorModel, QDialog *parent = nullptr);
    ~PoleSetupWindow();

private:
    void init();


signals:
    void sendNewPoleData(Pole newPoleData);

public slots:
    void setPoleModel(PoleModel *poleModel);
    void setMonitorModel(MonitorModel *monitorModel);


private:
    Ui::PoleSetupWindow *ui;

private:
    // data
    Pole m_poleData;

private:
    // model pointers
    PoleModel *poleModel;
    MonitorModel *monitorModel;


};

#endif // POLESETUPWINDOW_H
