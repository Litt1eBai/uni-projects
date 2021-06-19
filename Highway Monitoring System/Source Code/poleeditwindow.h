#ifndef POLEEDITWINDOW_H
#define POLEEDITWINDOW_H

#include <QDialog>
#include <QStandardItemModel>
#include <QDataWidgetMapper>
#include "polemodel.h"
#include "monitormodel.h"
#include <QAbstractTableModel>

namespace Ui {
class poleEditWindow;
}

class PoleEditWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PoleEditWindow(QWidget *parent = nullptr);
    explicit PoleEditWindow(PoleModel *poleModel, MonitorModel *monitorModel, QWidget *parent = nullptr);
    ~PoleEditWindow();

    void updateModel();


public slots:
    void setPoleModel(PoleModel *poleModel);
    void setMonitorModel(MonitorModel *monitorModel);
    void setPoleModelIndex(const QModelIndex &index);
    void setPassedPoleModelData(Pole currentPoleData);

private:
    void init();
    void closeEvent(QCloseEvent *event);
    void setAssociatedMonitorDataInWidget(MonitorDeviceType type, QString deviceCode);

signals:
    void updatedData(Pole data);
    void updateDataToModel(Pole data, QModelIndex &currentIndex);

private:
    Ui::poleEditWindow *ui;

    // model
    QModelIndex currentPoleModelIndex;
    PoleModel *poleModel;
    MonitorModel *monitorModel;

    // Data
    Pole currentPoleData;

};

#endif // POLEEDITWINDOW_H
