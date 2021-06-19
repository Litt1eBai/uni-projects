#ifndef RECORD_H
#define RECORD_H

#include <QString>

class Record
{
protected:
    char recordNo[10];
    char deviceCode[10];
    char poleCode[8];

public:
    Record();
    Record(char* deviceCode, char* poleCode);
    Record(const Record& rec);
    void setRecoedNo(char *recordNo);
    void setDeviceCode(char *deviceCode);
    void setPoleCode(char *poleCode);
    QString getDeviceCode();
    QString getPoleCode();
    QString getRecordNo();
    void getDeviceCode(char *dest);
    void getPoleCode(char *dest);
    void getRecordNo(char *dest);
};

#endif // RECORD_H
