#ifndef CELLULARRECORD_H
#define CELLULARRECORD_H

#include "basicheader.h"
#include "record.h"
#include <QDateTime>

class CellularRecord: public Record
{
    char IMEI[c_IMEIDigit];
    QDateTime recordTime;
public:
    CellularRecord();
    CellularRecord(char* deviceCode, char* poleCode, char* recordNo);
    CellularRecord(const CellularRecord& cellularRec);
    void setIMEI(char* IMEI);
    void setRecordTime(QDateTime time);
    void getIMEI(char* dest);
    QString getIMEI() const;
    QString getIMEI();
    QDateTime getRecordTime();
    QDateTime getRecordTime() const;
};

#endif // CELLULARRECORD_H
