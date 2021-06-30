#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "polemodel.h"
#include "monitormodel.h"
#include "cellularrecordmodel.h"
#include "cctvrecordmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void init();


private:
    Ui::MainWindow *ui;

    // models
    PoleModel poleModel;
    MonitorModel monitorModel;
    CellularRecordModel cellularRecordModel;
    CCTVRecordModel cctvRecordModel;

};
#endif // MAINWINDOW_H
