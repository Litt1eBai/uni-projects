#ifndef CCTVRECORDTABLEVIEWWIDGET_H
#define CCTVRECORDTABLEVIEWWIDGET_H

#include "cctvrecordmodel.h"
#include <QWidget>

namespace Ui {
class CCTVRecordTableViewWidget;
}

class CCTVRecordTableViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CCTVRecordTableViewWidget(QWidget *parent = nullptr);
    ~CCTVRecordTableViewWidget();

public:
    void initialise(CCTVRecordModel *cctvRecordModel);

private:
    void init();

private:
    Ui::CCTVRecordTableViewWidget *ui;

private:
    CCTVRecordModel *cctvRecordModel;

};

#endif // CCTVRECORDTABLEVIEWWIDGET_H
