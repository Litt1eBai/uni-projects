//#include "trafficrecord.h"
//#include <string.h>


//TrafficRecord::TrafficRecord() {
//    strcpy(this->vehicleRegistrationNo, "NoRegNo.");
//    this->vehicleRegionOfRegistration = Region::CQ;
//    this->vehicleColour = Colour::Black;
//    this->vehicleRegistrationType = VehicleType::Civilian;
//    this->vehicleSpeed = 0;
//    this->recordTime.currentDateTime();
//}

//TrafficRecord::TrafficRecord(char* deviceCode, char* poleCode)
//    : Record(deviceCode, poleCode){}

//TrafficRecord::TrafficRecord(const TrafficRecord& trafficRec)
//    :Record((char*)trafficRec.deviceCode, (char*)trafficRec.poleCode), recordTime(trafficRec.recordTime) {
//    strcpy_s(this->vehicleRegistrationNo, c_VehicleRegistrationNoLength, trafficRec.vehicleRegistrationNo);
//    this->vehicleRegionOfRegistration = trafficRec.vehicleRegionOfRegistration;
//    this->vehicleColour = trafficRec.vehicleColour;
//    this->vehicleRegistrationType = trafficRec.vehicleRegistrationType;
//    this->vehicleSpeed = trafficRec.vehicleSpeed;
//}

//void TrafficRecord::setRegistrationNo(char* regNo) {
//    strcpy_s(this->vehicleRegistrationNo, c_VehicleRegistrationNoLength, regNo);
//}

//void TrafficRecord::setRegistrationRegion(Region regRegion) {
//    this->vehicleRegionOfRegistration = regRegion;
//}

//void TrafficRecord::setVehicleColour(Colour colour) {
//    this->vehicleColour = colour;
//}

//void TrafficRecord::setVehicleType(VehicleType type) {
//    this->vehicleRegistrationType = type;
//}

//void TrafficRecord::setSpeed(double speed) {
//    this->vehicleSpeed = speed;
//}

//void TrafficRecord::setRecordTime(QDateTime time) {
//    this->recordTime = time;
//}

//QString TrafficRecord::getVehicleRegistrationNo() {
//    return QString(this->vehicleRegistrationNo);
//}
//QString TrafficRecord::getVehicleRegistrationNo() const {
//    return QString(this->vehicleRegistrationNo);
//}
//void TrafficRecord::getVehicleRegistrationNo(char* dest) {
//    strcpy_s(dest, c_VehicleRegistrationNoLength, this->vehicleRegistrationNo);
//}

//Region TrafficRecord::getRegistrationRegion() {
//    return vehicleRegionOfRegistration;
//}

//Region TrafficRecord::getRegistrationRegion() const {
//    return vehicleRegionOfRegistration;
//}

//Colour TrafficRecord::getVehicleColour() {
//    return vehicleColour;
//}
//Colour TrafficRecord::getVehicleColour() const {
//    return vehicleColour;
//}
//VehicleType TrafficRecord::getRegistrationType() {
//    return vehicleRegistrationType;
//}
//VehicleType TrafficRecord::getRegistrationType() const {
//    return vehicleRegistrationType;
//}
//double TrafficRecord::getSpeed() {
//    return vehicleSpeed;
//}
//double TrafficRecord::getSpeed() const {
//    return vehicleSpeed;
//}
//QDateTime TrafficRecord::getRecordTime() {
//    return recordTime;
//}
//QDateTime TrafficRecord::getRecordTime() const {
//    return recordTime;
//}
