#ifndef CCTVSURVEILLANCEDEVICE_H
#define CCTVSURVEILLANCEDEVICE_H

#include "surveillancedevice.h"

class CCTVSurveillanceDevice: public SurveillanceDevice
{
public:
    CCTVSurveillanceDevice();
    CCTVSurveillanceDevice(char* deviceCode);
    CCTVSurveillanceDevice(char* deviceCode, DeviceWorkStatus workStatus,
                           char* deviceDescription, QDateTime dateOfInstallation);
};

#endif // CCTVSURVEILLANCEDEVICE_H
