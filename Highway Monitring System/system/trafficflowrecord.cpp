#include "trafficflowrecord.h"
#include <string.h>
//char vehicleRegistrationNo[6];
//Region regionOfRegistration;
//Colour vehicleColour;
//VehicleType registrationType;
//double vehicleSpeed;
//DateTime time;
TrafficFlowRecord::TrafficFlowRecord() {
    strcpy(this->vehicleRegistrationNo, "NoRegNo.");
    this->vehicleRegionOfRegistration = Region::Chungking;
    this->vehicleColour = Colour::black;
    this->vehicleRegistrationType = VehicleType::civilian;
    this->vehicleSpeed = 0;
    this->recordTime.currentDateTime();
}

TrafficFlowRecord::TrafficFlowRecord(char* deviceCode, char* poleCode)
    : Record(deviceCode, poleCode){}

TrafficFlowRecord::TrafficFlowRecord(const TrafficFlowRecord& trafficRec)
    :Record((char*)trafficRec.deviceCode, (char*)trafficRec.poleCode), recordTime(trafficRec.recordTime) {
    strcpy(this->vehicleRegistrationNo, trafficRec.vehicleRegistrationNo);
    this->vehicleRegionOfRegistration = trafficRec.vehicleRegionOfRegistration;
    this->vehicleColour = trafficRec.vehicleColour;
    this->vehicleRegistrationType = trafficRec.vehicleRegistrationType;
    this->vehicleSpeed = trafficRec.vehicleSpeed;
}

void TrafficFlowRecord::setRegistrationNo(char* regNo) {
    strcpy(this->vehicleRegistrationNo, regNo);
}

void TrafficFlowRecord::setRegistrationRegion(Region regRegion) {
    this->vehicleRegionOfRegistration = regRegion;
}

void TrafficFlowRecord::setVehicleColour(Colour colour) {
    this->vehicleColour = colour;
}

void TrafficFlowRecord::setVehicleType(VehicleType type) {
    this->vehicleRegistrationType = type;
}

void TrafficFlowRecord::setSpeed(double speed) {
    this->vehicleSpeed = speed;
}

void TrafficFlowRecord::setRecordTime(QDateTime time) {
    this->recordTime = time;
}

QString TrafficFlowRecord::getVehicleRegistrationNo() {
    return QString(this->vehicleRegistrationNo);
}

void TrafficFlowRecord::getVehicleRegistrationNo(char* dest) {
    strcpy(dest, this->vehicleRegistrationNo);
}

Region TrafficFlowRecord::getRegistrationRegion() {
    return vehicleRegionOfRegistration;
}

QString TrafficFlowRecord::getRegistrationRegionStr() {
    QString str = "Not Implimented";
    return str;
}

Colour TrafficFlowRecord::getVehicleColour() {
    return vehicleColour;
}

QString TrafficFlowRecord::getVehicleColourStr() {
    QString str = "Not Implimented";
    return str;
}

VehicleType TrafficFlowRecord::getRegistrationType() {
    return vehicleRegistrationType;
}

QString TrafficFlowRecord::getRegistrationTypeStr() {
    QString str = "Not Implimented";
    return str;
}

double TrafficFlowRecord::getSpeed() {
    return vehicleSpeed;
}

QDateTime TrafficFlowRecord::getRecordTime() {
    return recordTime;
}
