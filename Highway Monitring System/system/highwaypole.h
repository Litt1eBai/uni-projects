#ifndef HIGHWAYPOLE_H
#define HIGHWAYPOLE_H

#include "basicHeader.h"
#include <math.h>

class HighwayPole
{
    double longitude;
    double latitude;
    char poleCode[7];
    char surveillanceDeviceInstallation[3][10];
    char description[200];
public:
    HighwayPole(double longitude, double latitude, char*poleCode);
    HighwayPole(double longitude, double latitude, char* poleCode, char* description);
    void setPosition(double longitude, double latitude);
    void setLongitude(double longitude);
    void setLatitude(double latitude);
    void setDescription(char* description);
    void setPoleCode(char* poleCode);
    void addSurveillanceDevice(SurveillanceDeviceType type, char* deviceCode);
    void removeSurveillanceDevice(SurveillanceDeviceType type);
    double getLongitude();
    double getLatitude();
    QString getPoleCode();
    QString getDeviceCode(SurveillanceDeviceType type);
    QString getDescription();
    void getPoleCode(char* dest);
    void getDeviceCode(SurveillanceDeviceType type, char* dest);
    void getDescription(char* dest);
    friend double getDistance(HighwayPole pole1, HighwayPole pole2);
};

double getDistance(HighwayPole pole1, HighwayPole pole2) {
    return sqrt((pole1.latitude - pole2.latitude) *(pole1.latitude - pole2.latitude) -
            (pole1.longitude - pole2.longitude) * (pole1.longitude - pole2.longitude));
}

#endif // HIGHWAYPOLE_H
