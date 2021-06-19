#include "cellularrecord.h"

#include <string.h>

CellularRecord::CellularRecord() {
    strcpy_s(this->IMEI, 12, "NoIMEI");
    this->recordTime.currentDateTime();
}

CellularRecord::CellularRecord(char* deviceCode, char* poleCode)
    : Record(deviceCode, poleCode) {}
CellularRecord::CellularRecord(const CellularRecord& cellularRec)
    : Record((char*)cellularRec.deviceCode, (char*)cellularRec.poleCode) {
    strcpy_s(this->IMEI, 12, cellularRec.IMEI);
    this->recordTime = cellularRec.recordTime;
}

void CellularRecord::setIMEI(char* IMEI) {
    strcpy_s(this->IMEI, 12, IMEI);
}

void CellularRecord::setRecordTime(QDateTime time) {
    this->recordTime = time;
}

void CellularRecord::getIMEI(char* dest) {
    strcpy_s(dest, 12, this->IMEI);
}

QString CellularRecord::getIMEI() {
    return QString(this->IMEI);
}

QDateTime CellularRecord::getRecordTime() {
    return this->recordTime;
}

