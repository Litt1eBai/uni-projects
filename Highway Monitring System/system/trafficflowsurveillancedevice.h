#ifndef TRAFFICFLOWSURVEILLANCEDEVICE_H
#define TRAFFICFLOWSURVEILLANCEDEVICE_H

#include "surveillancedevice.h"

class TrafficFlowSurveillanceDevice: public SurveillanceDevice
{
public:
    TrafficFlowSurveillanceDevice();
    TrafficFlowSurveillanceDevice(char* deviceCode);
    TrafficFlowSurveillanceDevice(char* deviceCode, DeviceWorkStatus workStatus,
                           char* deviceDescription, QDateTime dateOfInstallation);
};

#endif // TRAFFICFLOWSURVEILLANCEDEVICE_H
