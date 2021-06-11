#include "highwaypole.h"
#include <string.h>

HighwayPole::HighwayPole(double longitude, double latitude, char*poleCode)
    : longitude(longitude), latitude(latitude) {
    strcpy(this->poleCode, poleCode);
    for (int i = 0; i < 3; i++) {
        strcpy(this->surveillanceDeviceInstallation[i], "");
    }
}
HighwayPole::HighwayPole(double longitude, double latitude, char* poleCode, char* description)
    : longitude(longitude), latitude(latitude) {
    strcpy(this->poleCode, poleCode);
    strcpy(this->description, description);
    for (int i = 0; i < 3; i++) {
        strcpy(this->surveillanceDeviceInstallation[i], "");
    }
}
void HighwayPole::setPosition(double longitude, double latitude) {
    this->longitude = longitude;
    this->latitude = latitude;
}
void HighwayPole::setLongitude(double longitude) {
    this->longitude = longitude;
}
void HighwayPole::setLatitude(double latitude) {
    this->latitude = latitude;
}
void HighwayPole::setDescription(char* description) {
    strcpy(this->description, description);
}
void HighwayPole::setPoleCode(char* poleCode) {
    strcpy(this->poleCode, poleCode);
}
void HighwayPole::addSurveillanceDevice(SurveillanceDeviceType type, char* deviceCode) {
    strcpy(this->surveillanceDeviceInstallation[(int)type], deviceCode);
}
void HighwayPole::removeSurveillanceDevice(SurveillanceDeviceType type) {
    strcpy(this->surveillanceDeviceInstallation[(int)type], "");
}
double HighwayPole::getLongitude() {
    return longitude;
}
double HighwayPole::getLatitude() {
    return latitude;
}

QString HighwayPole::getPoleCode() {
    return QString(this->poleCode);
}

QString HighwayPole::getDeviceCode(SurveillanceDeviceType type) {
    return QString(this->surveillanceDeviceInstallation[(int)type]);
}

QString HighwayPole::getDescription() {
    return QString(this->description);
}
void HighwayPole::getPoleCode(char* dest) {
    strcpy(dest, this->poleCode);
}
void HighwayPole::getDeviceCode(SurveillanceDeviceType type, char* dest) {
    strcpy(dest, this->surveillanceDeviceInstallation[(int)type]);
}
void HighwayPole::getDescription(char* dest) {
    strcpy(dest, this->description);
}
