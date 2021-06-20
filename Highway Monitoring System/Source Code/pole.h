#ifndef HIGHWAYPOLE_H
#define HIGHWAYPOLE_H

#include "basicheader.h"
#include <QString>

class Pole
{
    double longitude;
    double latitude;
    char poleCode[c_PoleCodeDigit];
    char deviceInstallation[3][c_DeviceCodeDiget];
    char description[c_DescriptionLength];
public:
    Pole(double longitude, double latitude);
    Pole(double longitude, double latitude, char*poleCode);
    Pole(double longitude, double latitude, char* poleCode, char* description);
    void setPosition(double longitude, double latitude);
    void setLongitude(double longitude);
    void setLatitude(double latitude);
    void setDescription(char* description);
    void setPoleCode(char* poleCode);
    void addMonitor(MonitorDeviceType type, char* deviceCode);
    void removeMonitor(MonitorDeviceType type);
    double getLongitude();
    double getLatitude();
    QString getPoleCode();
    QString getDeviceCode(MonitorDeviceType type);
    QString getDescription();
    void getPoleCode(char* dest);
    void getDeviceCode(MonitorDeviceType type, char* dest);
    void getDescription(char* dest);
    QString getPoleCode() const;
    QString getDeviceCode(MonitorDeviceType type) const;
    QString getDescription() const;
    double getLongitude() const;
    double getLatitude() const;
};

#endif // HIGHWAYPOLE_H
