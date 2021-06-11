#ifndef SURVEILLANCEDEVICE_H
#define SURVEILLANCEDEVICE_H

#include "basicHeader.h"
#include <QDateTime>

class SurveillanceDevice
{
protected:
    char deviceCode[11];
    SurveillanceDeviceType deviceType;
    DeviceWorkStatus deviceWorkStatus;
    char deviceDescription[100];
    QDateTime dateOfInstallation;
public:
    SurveillanceDevice();
    SurveillanceDevice(char* deviceCode, SurveillanceDeviceType deviceType,
                       DeviceWorkStatus workStatus, char* deviceDescription,
                       QDateTime dateOfInstallation);
    SurveillanceDevice(const SurveillanceDevice& device);
    void setDevice(SurveillanceDeviceType type, char* code);
    void setDeviceCode(char* deviceCode);
    void setDeviceType(SurveillanceDeviceType type);
    void down();
    void running();
    void setDescription(char* description);
    void setInstallationTime(QDateTime time);
    QString getDeviceCode();
    void getDeviceCode(char* dest);
    SurveillanceDeviceType getDeviceType();
    DeviceWorkStatus getWorkStatus();
    QString getDescription();
    void getDescription(char* dest);
    QDateTime getInstallationDate();
};

#endif // SURVEILLANCEDEVICE_H
