#include "trafficflowsurveillancedevice.h"

TrafficFlowSurveillanceDevice::TrafficFlowSurveillanceDevice() {
    this->deviceType = SurveillanceDeviceType::TrafficFlow;
}

TrafficFlowSurveillanceDevice::TrafficFlowSurveillanceDevice(char* deviceCode) {
    strcpy(this->deviceCode, deviceCode);
}

TrafficFlowSurveillanceDevice::TrafficFlowSurveillanceDevice(
        char* deviceCode, DeviceWorkStatus workStatus,
        char* deviceDescription, QDateTime dateOfInstallation)
    : SurveillanceDevice(deviceCode, SurveillanceDeviceType::TrafficFlow,
                       workStatus, deviceDescription, dateOfInstallation) {}
