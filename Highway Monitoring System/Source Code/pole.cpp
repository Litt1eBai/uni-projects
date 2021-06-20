 #include "pole.h"
#include <string.h>
#include <QMessageBox>

Pole::Pole(double longitude, double latitude, char*poleCode)
    : longitude(longitude), latitude(latitude) {
    strcpy_s(this->poleCode, c_PoleCodeDigit, poleCode);
    for (int i = 0; i < 3; i++) {
        strcpy_s(this->deviceInstallation[i], c_DeviceCodeDiget, "");
    }
}
Pole::Pole(double longitude, double latitude)
    : longitude(longitude), latitude(latitude) {
    strcpy_s(this->poleCode, c_PoleCodeDigit, "000000");
    for (int i = 0; i < 3; i++) {
        strcpy(this->deviceInstallation[i], "");
    }
}
Pole::Pole(double longitude, double latitude, char* poleCode, char* description)
    : longitude(longitude), latitude(latitude) {
    strcpy_s(this->poleCode, c_PoleCodeDigit, poleCode);
    strcpy_s(this->description, c_DescriptionLength, description);
    for (int i = 0; i < 3; i++) {
        strcpy(this->deviceInstallation[i], "");
    }
}
void Pole::setPosition(double longitude, double latitude) {
    this->longitude = longitude;
    this->latitude = latitude;
}
void Pole::setLongitude(double longitude) {
    this->longitude = longitude;
}
void Pole::setLatitude(double latitude) {
    this->latitude = latitude;
}
void Pole::setDescription(char* description) {
    if (strlen(description) > c_DescriptionLength) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","string length out of range");
        messageBox.setFixedSize(500,200);
        return;
    }
    strcpy_s(this->description, c_DescriptionLength, description);
}
void Pole::setPoleCode(char* poleCode) {
    if (strlen(poleCode) > c_PoleCodeDigit) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","string length out of range");
        messageBox.setFixedSize(500,200);
        return;
    }
    strcpy_s(this->poleCode, c_PoleCodeDigit, poleCode);
}
void Pole::addMonitor(MonitorDeviceType type, char* deviceCode) {
    if (strlen(deviceCode) > c_DeviceCodeDiget) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","string length out of range");
        messageBox.setFixedSize(500,200);
        return;
    }
    strcpy_s(this->deviceInstallation[(int)type], c_DeviceCodeDiget, deviceCode);
}
void Pole::removeMonitor(MonitorDeviceType type) {
    strcpy_s(this->deviceInstallation[(int)type], c_DeviceCodeDiget, "");
}
double Pole::getLongitude() {
    return longitude;
}
double Pole::getLongitude() const {
    return longitude;
}
double Pole::getLatitude() {
    return latitude;
}
double Pole::getLatitude() const {
    return latitude;
}
QString Pole::getPoleCode() {
    return QString(this->poleCode);
}
QString Pole::getPoleCode() const {
    return QString(this->poleCode);
}
QString Pole::getDeviceCode(MonitorDeviceType type) {
    return QString(this->deviceInstallation[(int)type]);
}
QString Pole::getDeviceCode(MonitorDeviceType type) const {
    return QString(this->deviceInstallation[(int)type]);
}
QString Pole::getDescription() {
    return QString(this->description);
}
QString Pole::getDescription() const {
    return QString(this->description);
}
void Pole::getPoleCode(char* dest) {
    strcpy_s(dest, c_PoleCodeDigit, this->poleCode);
}
void Pole::getDeviceCode(MonitorDeviceType type, char* dest) {
    strcpy_s(dest, c_DeviceCodeDiget, this->deviceInstallation[(int)type]);
}
void Pole::getDescription(char* dest) {
    strcpy_s(dest, c_DescriptionLength, this->description);
}
