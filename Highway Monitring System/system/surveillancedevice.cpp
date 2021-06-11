#include "surveillancedevice.h"
#include <string.h>

//char DeviceCode[11];
//SurveillanceDeviceType deviceType;
//DeviceWorkStatus deviceWorkStatus;
//char deviceDescription[100];
//QDateTime dateOfInstallation;

SurveillanceDevice::SurveillanceDevice() {
    strcpy(this->deviceCode, "NoCode");
    strcpy(this->deviceDescription, "NoDescription");
    this->deviceType = SurveillanceDeviceType::abstruct;
    this->deviceWorkStatus = DeviceWorkStatus::notInstalled;
    this->dateOfInstallation.currentDateTime();
}

SurveillanceDevice::SurveillanceDevice
        (char* deviceCode, SurveillanceDeviceType deviceType,
         DeviceWorkStatus workStatus,
        char* deviceDescription, QDateTime dateOfInstallation)
    : dateOfInstallation(dateOfInstallation), deviceType(deviceType),
      deviceWorkStatus(workStatus){
    strcpy(this->deviceCode, deviceCode);
    strcpy(this->deviceDescription, deviceDescription);
}

SurveillanceDevice::SurveillanceDevice(const SurveillanceDevice& device) {
    strcpy(this->deviceCode, device.deviceCode);
    strcpy(this->deviceDescription, device.deviceDescription);
    this->deviceWorkStatus = device.deviceWorkStatus;
    this->deviceType = device.deviceType;
}

void SurveillanceDevice::setDevice(SurveillanceDeviceType type, char* code) {
    this->deviceType = type;
    strcpy(this->deviceCode, code);
}

void SurveillanceDevice::setDeviceCode(char* deviceCode) {
    strcpy(this->deviceCode, deviceCode);
}

void SurveillanceDevice::setDeviceType(SurveillanceDeviceType type) {
    this->deviceType = type;
}

void SurveillanceDevice::down() {
    this->deviceWorkStatus = DeviceWorkStatus::down;
}

void SurveillanceDevice::running() {
    this->deviceWorkStatus = DeviceWorkStatus::running;
}

void SurveillanceDevice::setDescription(char* description) {
    strcpy(this->deviceDescription, description);
}

void SurveillanceDevice::setInstallationTime(QDateTime time) {
    this->dateOfInstallation = time;
}

QString SurveillanceDevice::getDeviceCode() {
    return QString(this->deviceCode);
}

void SurveillanceDevice::getDeviceCode(char* dest) {
    strcpy(dest, this->deviceCode);
}

SurveillanceDeviceType SurveillanceDevice::getDeviceType() {
    return this->deviceType;
}

DeviceWorkStatus SurveillanceDevice::getWorkStatus() {
    return deviceWorkStatus;
}

QString SurveillanceDevice::getDescription() {
    return QString(this->deviceDescription);
}

void SurveillanceDevice::getDescription(char* dest) {
    strcpy(dest, this->deviceDescription);
}

QDateTime SurveillanceDevice::getInstallationDate() {
    return dateOfInstallation;
}
