#include "cctvrecord.h"

CCTVRecord::CCTVRecord():
    startTime(QDateTime().currentDateTime()),
    endTime(QDateTime().currentDateTime())
{
    strcpy_s(this->description, c_DescriptionLength, "NoDescription");
    strcpy_s(this->filePath, c_filePathLength, "NotFound");
}
CCTVRecord::CCTVRecord(const CCTVRecord& CCTVrec)
    : Record((char*)CCTVrec.deviceCode, (char*)CCTVrec.poleCode) {
    strcpy_s(this->description, c_DescriptionLength, CCTVrec.description);
    strcpy_s(this->filePath, c_filePathLength, CCTVrec.filePath);
    this->startTime = CCTVrec.startTime;
    this->endTime = CCTVrec.endTime;
}
void CCTVRecord::setDescription(char* description) {
    strcpy_s(this->description, c_DescriptionLength, description);
}
void CCTVRecord::setFilePath(char* filePath) {
    strcpy_s(this->filePath, c_filePathLength, filePath);
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
QString CCTVRecord::getDescription() const {
    QString description(this->description);
    return description;
}
QString CCTVRecord::getFilePath() {
    QString filePath(this->filePath);
    return filePath;
}
QString CCTVRecord::getFilePath() const {
    QString filePath(this->filePath);
    return filePath;
}
void CCTVRecord::getDescription(char* dest) {
    strcpy_s(dest, c_DescriptionLength, this->description);
}
void CCTVRecord::getFilePath(char* dest) {
    strcpy_s(dest, c_filePathLength, this->filePath);
}
QDateTime CCTVRecord::getStartTime() {
    return this->startTime;
}
QDateTime CCTVRecord::getStartTime() const {
    return this->startTime;
}
QDateTime CCTVRecord::getEndTime() {
    return this->endTime;
}
QDateTime CCTVRecord::getEndTime() const{
    return this->endTime;
}
