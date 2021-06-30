#ifndef CCTVRECORD_H
#define CCTVRECORD_H

#include "basicheader.h"
#include "record.h"
#include <QDateTime>

class CCTVRecord: public Record
{
    char description[c_DescriptionLength];
    QDateTime startTime;
    QDateTime endTime;
    char filePath[c_filePathLength];
public:
    CCTVRecord();
    CCTVRecord(const CCTVRecord& CCTVrec);
    void setDescription(char* description);
    void setFilePath(char* filePath);
    void setStartTime(QDateTime start);
    void setEndTime(QDateTime end);
    QString getDescription();
    QString getFilePath();
    QString getDescription() const;
    QString getFilePath() const;
    void getDescription(char* dest);
    void getFilePath(char* dest);
    QDateTime getStartTime();
    QDateTime getEndTime();
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;
};

#endif // CCTVRECORD_H
