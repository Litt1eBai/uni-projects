#ifndef RECORD_H
#define RECORD_H

#include "basicheader.h"
#include <QString>

class Record
{
protected:
    char recordNo[c_recordCodeDigit];
    char deviceCode[c_DeviceCodeDiget];
    char poleCode[c_PoleCodeDigit];

public:
    Record();
    Record(char* deviceCode, char* poleCode);
    Record(char* deviceCode, char* poleCode, char* recordNo);
    Record(const Record& rec);
    void setRecoedNo(char *recordNo);
    void setDeviceCode(char *deviceCode);
    void setPoleCode(char *poleCode);
    QString getDeviceCode();
    QString getPoleCode();
    QString getRecordNo();
    QString getDeviceCode() const;
    QString getPoleCode() const;
    QString getRecordNo() const;
    void getDeviceCode(char *dest);
    void getPoleCode(char *dest);
    void getRecordNo(char *dest);
};

#endif // RECORD_H
