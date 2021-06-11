#ifndef TRAFFICFLOWRECORD_H
#define TRAFFICFLOWRECORD_H

#include <QString>
#include "record.h"
#include "basicHeader.h"
#include "record.h"
#include <QDateTime>
#include <QString>

class TrafficFlowRecord: public Record
{
    char vehicleRegistrationNo[6];
    Region vehicleRegionOfRegistration;
    Colour vehicleColour;
    VehicleType vehicleRegistrationType;
    double vehicleSpeed;
    QDateTime recordTime;
public:
    TrafficFlowRecord();
    TrafficFlowRecord(char* deviceCode, char* poleCode);
    TrafficFlowRecord(const TrafficFlowRecord& trafficRec);
    void setRegistrationNo(char* regNo);
    void setRegistrationRegion(Region regRegion);
    void setVehicleColour(Colour colour);
    void setVehicleType(VehicleType type);
    void setSpeed(double speed);
    void setRecordTime(QDateTime time);
    QString getVehicleRegistrationNo();
    void getVehicleRegistrationNo(char* dest);
    Region getRegistrationRegion();
    QString getRegistrationRegionStr();
    Colour getVehicleColour();
    QString getVehicleColourStr();
    VehicleType getRegistrationType();
    QString getRegistrationTypeStr();
    double getSpeed();
    QDateTime getRecordTime();
};

#endif // TRAFFICFLOWRECORD_H
