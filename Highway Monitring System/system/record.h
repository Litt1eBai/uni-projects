#ifndef RECORD_H
#define RECORD_H

#include <QString>

class Record
{
protected:
    char deviceCode[10];
    char poleCode[7];
public:
    Record();
    Record(char* deviceCode, char* poleCode);
    Record(const Record& rec);
    void setDeviceCode(char* deviceCode);
    void setPoleCode(char* poleCode);
    QString getDeviceCode();
    QString getPoleCode();
    void getDeviceCode(char* dest);
    void getPoleCode(char* dest);
};

#endif // RECORD_H
