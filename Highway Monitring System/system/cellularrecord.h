#ifndef CELLULARRECORD_H
#define CELLULARRECORD_H

#include "record.h"
#include "basicHeader.h"

class CellularRecord: public Record
{
    char IMEI[11];
    QDateTime recordTime;
public:
    CellularRecord();
    CellularRecord(char* deviceCode, char* poleCode);
    CellularRecord(const CellularRecord& cellularRec);
    void setIMEI(char* IMEI);
    void setRecordTime(QDateTime time);
    void getIMEI(char* dest);
    QString getIMEI();
    QDateTime getRecordTime();
};

#endif // CELLULARRECORD_H
