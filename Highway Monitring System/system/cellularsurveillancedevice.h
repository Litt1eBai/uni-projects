#ifndef CELLULARSURVEILLANCEDEVICE_H
#define CELLULARSURVEILLANCEDEVICE_H

#include "surveillancedevice.h"

class CellularSurveillanceDevice: public SurveillanceDevice
{
public:
    CellularSurveillanceDevice();
    CellularSurveillanceDevice(char* deviceCode);
    CellularSurveillanceDevice(char* deviceCode, DeviceWorkStatus workStatus,
                           char* deviceDescription, QDateTime dateOfInstallation);
};

#endif // CELLULARSURVEILLANCEDEVICE_H
