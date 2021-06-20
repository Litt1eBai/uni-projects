#ifndef MONITOR_H
#define MONITOR_H

#include "basicheader.h"
#include <QDateTime>

class Monitor
{
protected:
    char deviceCode[c_DeviceCodeDiget];
    MonitorDeviceType deviceType;
    DeviceWorkStatus deviceWorkStatus;
    char deviceDescription[c_DescriptionLength];
    QDateTime dateOfInstallation;
public:
    Monitor();
    Monitor(char* deviceCode, MonitorDeviceType deviceType,
                       DeviceWorkStatus workStatus, char* deviceDescription,
                       QDateTime dateOfInstallation);
    Monitor(const Monitor& device);
    void setDevice(MonitorDeviceType type, char* code);
    void setDeviceCode(char* deviceCode);
    void setDeviceType(MonitorDeviceType type);
    void down();
    void running();
    void setDescription(char* description);
    void setDeviceWorkStatus(DeviceWorkStatus workStatus);
    void setInstallationTime(QDateTime time);
    QString getDeviceCode();
    QString getDeviceCode() const;
    void getDeviceCode(char* dest);
    MonitorDeviceType getDeviceType();
    MonitorDeviceType getDeviceType() const;
    DeviceWorkStatus getWorkStatus();
    DeviceWorkStatus getWorkStatus() const;
    QString getDescription();
    QString getDescription() const;
    void getDescription(char* dest);
    QDateTime getInstallationDate();
    QDateTime getInstallationDate() const;
};

#endif // MONITOR_H
