#include "monitor.h"

Monitor::Monitor():
    dateOfInstallation(QDateTime().currentDateTime()) {
    strcpy_s(this->deviceCode,c_DeviceCodeDiget, "NoCode");
    strcpy_s(this->deviceDescription, c_DescriptionLength, "NoDescription");
    this->deviceType = MonitorDeviceType::Abstract;
    this->deviceWorkStatus = DeviceWorkStatus::NotInstalled;
}

Monitor::Monitor
        (char* deviceCode, MonitorDeviceType deviceType,
         DeviceWorkStatus workStatus, char* deviceDescription, QDateTime dateOfInstallation):
    deviceType(deviceType), deviceWorkStatus(workStatus),
    dateOfInstallation(dateOfInstallation){

    strcpy_s(this->deviceCode, c_DeviceCodeDiget, deviceCode);
    strcpy_s(this->deviceDescription, c_DescriptionLength, deviceDescription);

}

Monitor::Monitor(const Monitor& device) {

    strcpy_s(this->deviceCode, c_DeviceCodeDiget, device.deviceCode);
    strcpy_s(this->deviceDescription, c_DescriptionLength, device.deviceDescription);
    this->deviceWorkStatus = device.deviceWorkStatus;
    this->deviceType = device.deviceType;
    this->dateOfInstallation = device.dateOfInstallation;

}

void Monitor::setDevice(MonitorDeviceType type, char* code) {

    this->deviceType = type;
    strcpy_s(this->deviceCode, c_DeviceCodeDiget, code);

}

void Monitor::setDeviceCode(char* deviceCode) {

    strcpy_s(this->deviceCode, c_DeviceCodeDiget, deviceCode);

}

void Monitor::setDeviceType(MonitorDeviceType type) {

    this->deviceType = type;

}

void Monitor::down() {

    this->deviceWorkStatus = DeviceWorkStatus::Down;

}

void Monitor::running() {

    this->deviceWorkStatus = DeviceWorkStatus::Running;

}

void Monitor::setDescription(char* description) {

    strcpy_s(this->deviceDescription, c_DescriptionLength, description);

}

void Monitor::setDeviceWorkStatus(DeviceWorkStatus workStatus){

    this->deviceWorkStatus = workStatus;

}

void Monitor::setInstallationTime(QDateTime time) {

    this->dateOfInstallation = time;

}

QString Monitor::getDeviceCode() {

    return QString(this->deviceCode);

}

QString Monitor::getDeviceCode() const {

    return QString(this->deviceCode);

}

void Monitor::getDeviceCode(char* dest) {

    strcpy_s(dest, c_DeviceCodeDiget, this->deviceCode);

}

MonitorDeviceType Monitor::getDeviceType() {

    return this->deviceType;

}

MonitorDeviceType Monitor::getDeviceType() const {

    return this->deviceType;

}

DeviceWorkStatus Monitor::getWorkStatus() {

    return deviceWorkStatus;

}

DeviceWorkStatus Monitor::getWorkStatus() const {

    return deviceWorkStatus;

}

QString Monitor::getDescription() {

    return QString(this->deviceDescription);

}

QString Monitor::getDescription() const {

    return QString(this->deviceDescription);

}

void Monitor::getDescription(char* dest) {

    strcpy_s(dest, c_DescriptionLength, this->deviceDescription);

}

QDateTime Monitor::getInstallationDate() {

    return this->dateOfInstallation;

}

QDateTime Monitor::getInstallationDate() const {

    return this->dateOfInstallation;

}
