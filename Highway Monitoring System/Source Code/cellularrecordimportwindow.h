#ifndef CELLULARRECORDIMPORTWINDOW_H
#define CELLULARRECORDIMPORTWINDOW_H

#include <cellularrecord.h>
#include <cellularrecordmodel.h>
#include <QVector>
#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class CellularRecordImportWindow;
}

class CellularRecordImportWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CellularRecordImportWindow(QWidget *parent = nullptr);
    explicit CellularRecordImportWindow(CellularRecordModel *cellularRecordModel, QWidget *parent = nullptr);
    ~CellularRecordImportWindow();

private:
    void init();
    void initialise(CellularRecordModel *cellularRecordModel);
    void importDataFromXlsx(QString filePath, int row);


private:
    Ui::CellularRecordImportWindow *ui;

private:
    CellularRecordModel *m_importedTempCellularRecordModel;

private:
    CellularRecordModel *cellularRecordModel;
    QFileSystemModel *fileSystemModel;

};

#endif // CELLULARRECORDIMPORTWINDOW_H
