#include "record.h"
#include <string.h>

Record::Record() {
    strcpy(this->deviceCode, "NoDevice");
    strcpy(this->poleCode, "NoPole");
}
Record::Record(char* deviceCode, char* poleCode) {
    strcpy(this->deviceCode, deviceCode);
    strcpy(this->poleCode, poleCode);
}
Record::Record(const Record& rec) {
    strcpy(this->poleCode, rec.poleCode);
    strcpy(this->deviceCode, rec.deviceCode);
}
void Record::setDeviceCode(char* deviceCode) {
    strcpy(this->deviceCode, deviceCode);
}
void Record::setPoleCode(char* poleCode) {
    strcpy(this->poleCode, poleCode);
}

QString Record::getDeviceCode() {
    return QString(this->deviceCode);
}

QString Record::getPoleCode() {
    return QString(this->poleCode);
}
void Record::getDeviceCode(char* dest) {
    strcpy(dest, this->deviceCode);
}
void Record::getPoleCode(char* dest) {
    strcpy(dest, this->poleCode);
}
