#ifndef TRAFFICRECORD_H
#define TRAFFICRECORD_H

#include "basicheader.h"
#include "record.h"
#include <QDateTime>

class TrafficRecord: public Record
{
//    Colour vehicleColour;
//    Region vehicleRegionOfRegistration;
    char vehicleRegistrationNo[c_VehicleRegistrationNoLength];
//    VehicleType vehicleRegistrationType;
    double vehicleSpeed;
    QDateTime recordTime;
public:
    TrafficRecord();
    TrafficRecord(char* deviceCode, char* poleCode);
    TrafficRecord(const TrafficRecord& trafficRec);
    void setRegistrationNo(char* regNo);
//    void setRegistrationRegion(Region regRegion);
//    void setVehicleColour(Colour colour);
//    void setVehicleType(VehicleType type);
    void setSpeed(double speed);
    void setRecordTime(QDateTime time);
    QString getVehicleRegistrationNo();
    QString getVehicleRegistrationNo() const;
    void getVehicleRegistrationNo(char* dest);
//    Region getRegistrationRegion();
//    Region getRegistrationRegion() const;
//    Colour getVehicleColour();
//    Colour getVehicleColour() const;
//    VehicleType getRegistrationType();
//    VehicleType getRegistrationType() const;
    double getSpeed();
    double getSpeed() const;
    QDateTime getRecordTime();
    QDateTime getRecordTime()const;

};
#endif // TRAFFICRECORD_H
