#include "cctvrecord.h"
#include <string.h>

//char description[200];
//char filePath[200];
//QDateTime startTime;
//QDateTime endTime;

CCTVRecord::CCTVRecord() {
    strcpy(this->description, "NoDescription");
    strcpy(this->filePath, "NotFound");
    this->startTime.currentDateTime();
    this->endTime.currentDateTime();
}
CCTVRecord::CCTVRecord(const CCTVRecord& CCTVrec)
    : Record((char*)CCTVrec.deviceCode, (char*)CCTVrec.poleCode) {
    strcpy(this->description, CCTVrec.description);
    strcpy(this->filePath, CCTVrec.filePath);
    this->startTime = CCTVrec.startTime;
    this->endTime = CCTVrec.endTime;
}
void CCTVRecord::setDescription(char* description) {
    strcpy(this->description, description);
}
void CCTVRecord::setFilePath(char* filePath) {
    strcpy(this->filePath, filePath);
}
void CCTVRecord::setStartTime(QDateTime start) {
    this->startTime = start;
}
void CCTVRecord::setEndTime(QDateTime end) {
    this->endTime = end;
}
QString CCTVRecord::getDescription() {
    QString description(this->description);
    return description;
}
QString CCTVRecord::getFilePath() {
    QString filePath(this->filePath);
    return filePath;
}
void CCTVRecord::getDescription(char* dest) {
    strcpy(dest, this->description);
}
void CCTVRecord::getFilePath(char* dest) {
    strcpy(dest, this->filePath);
}
QDateTime CCTVRecord::getStartTime() {
    return this->startTime;
}
QDateTime CCTVRecord::getEndTime() {
    return this->endTime;
}
