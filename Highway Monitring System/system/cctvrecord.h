#ifndef CCTVRECORD_H
#define CCTVRECORD_H

#include "record.h"
#include "basicHeader.h"

class CCTVRecord: public Record
{
    char description[200];
    char filePath[200];
    QDateTime startTime;
    QDateTime endTime;
public:
    CCTVRecord();
    CCTVRecord(const CCTVRecord& CCTVrec);
    void setDescription(char* description);
    void setFilePath(char* filePath);
    void setStartTime(QDateTime start);
    void setEndTime(QDateTime end);
    QString getDescription();
    QString getFilePath();
    void getDescription(char* dest);
    void getFilePath(char* dest);
    QDateTime getStartTime();
    QDateTime getEndTime();
};

#endif // CCTVRECORD_H
