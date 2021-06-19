#include "record.h"
#include <string.h>

Record::Record() {
    strcpy_s(this->deviceCode, 10, "NoDevice");
    strcpy_s(this->poleCode, 8, "NoPole");
}
Record::Record(char* deviceCode, char* poleCode) {
    strcpy_s(this->deviceCode, 10, deviceCode);
    strcpy_s(this->poleCode, 8, poleCode);
}
Record::Record(const Record& rec) {
    strcpy_s(this->poleCode, 10, rec.poleCode);
    strcpy_s(this->deviceCode, 8, rec.deviceCode);
}

void Record::setRecoedNo(char *recordNo)
{
    strcpy_s(this->recordNo, 10, recordNo);
}
void Record::setDeviceCode(char* deviceCode) {
    strcpy_s(this->deviceCode, 10, deviceCode);
}
void Record::setPoleCode(char* poleCode) {
    strcpy_s(this->poleCode, 8, poleCode);
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
void Record::getDeviceCode(char* dest) {
    strcpy_s(dest, 10, this->deviceCode);
}
void Record::getPoleCode(char* dest) {
    strcpy_s(dest, 8, this->poleCode);
}

void Record::getRecordNo(char *dest)
{
    strcpy_s(dest, 10, this->recordNo);
}

