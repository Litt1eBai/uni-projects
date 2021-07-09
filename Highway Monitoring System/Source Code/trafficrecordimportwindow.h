#ifndef TRAFFICRECORDIMPORTWINDOW_H
#define TRAFFICRECORDIMPORTWINDOW_H

#include "trafficrecord.h"
#include "trafficrecordmodel.h"
#include <QVector>
#include <QDialog>
#include <QFileSystemModel>

#include <QDialog>

namespace Ui {
class TrafficRecordImportWindow;
}

class TrafficRecordImportWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TrafficRecordImportWindow(QWidget *parent = nullptr);
    explicit TrafficRecordImportWindow(TrafficRecordModel *trafficRecordModel, QWidget *parent = nullptr);
    ~TrafficRecordImportWindow();

private:
    void init();
    void importDataFromXlsx(QString filePath, int rowCount);

private:
    TrafficRecordModel *m_importedTempTrafficRecordModel;

private:
    TrafficRecordModel *trafficRecordModel;
    QFileSystemModel *fileSystemModel;

private:
    Ui::TrafficRecordImportWindow *ui;
};

#endif // TRAFFICRECORDIMPORTWINDOW_H
