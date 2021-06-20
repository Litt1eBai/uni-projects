#include "record.h"
#include <string.h>
#include <QDebug>

Record::Record() {
    strcpy_s(this->deviceCode, c_DeviceCodeDiget, "NoDevice");
    strcpy_s(this->poleCode, c_PoleCodeDigit, "NoPole");
    strcpy_s(this->recordNo, c_recordCodeDigit, "0");
}
Record::Record(char* deviceCode, char* poleCode, char* recordNo) {
    strcpy_s(this->deviceCode, c_DeviceCodeDiget, deviceCode);
    strcpy_s(this->poleCode, c_PoleCodeDigit, poleCode);
    strcpy_s(this->recordNo, c_recordCodeDigit, recordNo);
}
Record::Record(const Record& rec) {
    strcpy_s(this->poleCode, c_PoleCodeDigit, rec.poleCode);
    strcpy_s(this->deviceCode, c_DeviceCodeDiget, rec.deviceCode);
    strcpy_s(this->recordNo, c_recordCodeDigit, rec.recordNo);
}

void Record::setRecoedNo(char *recordNo)
{
    strcpy_s(this->recordNo, c_recordCodeDigit, recordNo);
}

void Record::setDeviceCode(char* deviceCode) {
    strcpy_s(this->deviceCode, c_DeviceCodeDiget, deviceCode);
}
void Record::setPoleCode(char* poleCode) {
    strcpy_s(this->poleCode, c_PoleCodeDigit, poleCode);
}

QString Record::getDeviceCode() {
    return QString(this->deviceCode);
}

QString Record::getPoleCode() {
    return QString(this->poleCode);
}

QString Record::getRecordNo()
{
    return QString(this->recordNo);
}
QString Record::getDeviceCode() const {
    return QString(this->deviceCode);
}

QString Record::getPoleCode() const {
    return QString(this->poleCode);
}

QString Record::getRecordNo() const
{
    return QString(this->recordNo);
}
void Record::getDeviceCode(char* dest) {
    strcpy_s(dest, c_DeviceCodeDiget, this->deviceCode);
}
void Record::getPoleCode(char* dest) {
    strcpy_s(dest, c_PoleCodeDigit, this->poleCode);
}

void Record::getRecordNo(char *dest)
{
    strcpy_s(dest, c_recordCodeDigit, this->recordNo);
}

