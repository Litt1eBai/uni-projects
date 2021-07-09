#ifndef CCTVRECORDDISPLAYWIDGET_H
#define CCTVRECORDDISPLAYWIDGET_H

#include <QWidget>
#include "cctvrecordmodel.h"
#include "cctvrecordproxymodel.h"
#include <QDateTime>

namespace Ui {
class CCTVRecordDisplayWidget;
}

class CCTVRecordDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CCTVRecordDisplayWidget(QWidget *parent = nullptr);

    void initialise(CCTVRecordModel *cctvRecordModel);
    void setPoleCode(QString poleCode);

    ~CCTVRecordDisplayWidget();

private:
    void init();

private:
    Ui::CCTVRecordDisplayWidget *ui;

    CCTVRecordModel *cctvRecordModel;
    CCTVRecordProxyModel *cctvRecordProxyModel;
    QString m_poleCode;
    QDateTime m_start;
    QDateTime m_end;

};

#endif // CCTVRECORDDISPLAYWIDGET_H
