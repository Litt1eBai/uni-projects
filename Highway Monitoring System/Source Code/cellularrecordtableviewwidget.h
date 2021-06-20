#ifndef CELLULARRECORDTABLEVIEWWIDGET_H
#define CELLULARRECORDTABLEVIEWWIDGET_H

#include "cellularrecordmodel.h"
#include <QWidget>

namespace Ui {
class CellularRecordTableViewWidget;
}

class CellularRecordTableViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CellularRecordTableViewWidget(QWidget *parent = nullptr);
    void initialise(CellularRecordModel *cellularRecordModel);
    ~CellularRecordTableViewWidget();


private:

    void init();

private:
    Ui::CellularRecordTableViewWidget *ui;

private:

    CellularRecordModel *cellularRecordModel;

};

#endif // CELLULARRECORDTABLEVIEWWIDGET_H
