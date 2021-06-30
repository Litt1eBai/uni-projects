#include "cellularrecord.h"

#include <string.h>

CellularRecord::CellularRecord()
    :recordTime(QDateTime().currentDateTime())
{
    strcpy_s(this->IMEI, c_IMEIDigit, "NoIMEI");
}

CellularRecord::CellularRecord(char* deviceCode, char* poleCode, char* recordNo)
    : Record(deviceCode, poleCode, recordNo) {}

CellularRecord::CellularRecord(const CellularRecord& cellularRec)
    : Record((char*)cellularRec.deviceCode, (char*)cellularRec.poleCode, (char*)cellularRec.recordNo) {

    strcpy_s(this->IMEI, c_IMEIDigit, cellularRec.IMEI);
    this->recordTime = cellularRec.recordTime;

}

void CellularRecord::setIMEI(char* IMEI) {

    strcpy_s(this->IMEI, c_IMEIDigit, IMEI);

}

void CellularRecord::setRecordTime(QDateTime time) {

    this->recordTime = time;

}

void CellularRecord::getIMEI(char* dest) {

    strcpy_s(dest, c_IMEIDigit, this->IMEI);

}

QString CellularRecord::getIMEI() const {

    return QString(this->IMEI);

}

QString CellularRecord::getIMEI()
{
    return QString(this->IMEI);
}

QDateTime CellularRecord::getRecordTime() {

    return this->recordTime;

}
QDateTime CellularRecord::getRecordTime() const {

    return this->recordTime;

}

