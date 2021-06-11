#include "cellularrecord.h"
#include <string.h>

//char IMEI[11];
//QDateTime recordTime;

CellularRecord::CellularRecord() {
    strcpy(this->IMEI, "NoIMEI");
    this->recordTime.currentDateTime();
}
CellularRecord::CellularRecord(char* deviceCode, char* poleCode)
    : Record(deviceCode, poleCode) {}
CellularRecord::CellularRecord(const CellularRecord& cellularRec)
    : Record((char*)cellularRec.deviceCode, (char*)cellularRec.poleCode) {
    strcpy(this->IMEI, cellularRec.IMEI);
    this->recordTime = cellularRec.recordTime;
}
void CellularRecord::setIMEI(char* IMEI) {
    strcpy(this->IMEI, IMEI);
}
void CellularRecord::setRecordTime(QDateTime time) {
    this->recordTime = time;
}
void CellularRecord::getIMEI(char* dest) {
    strcpy(dest, this->IMEI);
}

QString CellularRecord::getIMEI() {
    return QString(this->IMEI);
}
QDateTime CellularRecord::getRecordTime() {
    return this->recordTime;
}
