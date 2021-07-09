#ifndef CCTVRECORDIMPORTWINDOW_H
#define CCTVRECORDIMPORTWINDOW_H

#include "cctvrecordmodel.h"
#include "record.h"
#include <QVector>
#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class CCTVRecordImportWindow;
}

class CCTVRecordImportWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CCTVRecordImportWindow(QWidget *parent = nullptr);
    explicit CCTVRecordImportWindow(CCTVRecordModel *cellularRecordModel, QWidget *parent = nullptr);
    ~CCTVRecordImportWindow();

private:
    void init();

private:
    Ui::CCTVRecordImportWindow *ui;

private:
    CCTVRecord m_cctvRecord;

private:
    CCTVRecordModel *cctvRecordModel;
    QFileSystemModel *fileSystemModel;

};

#endif // CCTVRECORDIMPORTWINDOW_H
