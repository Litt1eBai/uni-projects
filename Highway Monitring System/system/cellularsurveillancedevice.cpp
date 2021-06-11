#include "cellularsurveillancedevice.h"
#include "basicHeader.h"

CellularSurveillanceDevice::CellularSurveillanceDevice() {
    this->deviceType = SurveillanceDeviceType::Cellular;
}

CellularSurveillanceDevice::CellularSurveillanceDevice(char* deviceCode) {
    strcpy(this->deviceCode, deviceCode);
}
CellularSurveillanceDevice::CellularSurveillanceDevice(
        char* deviceCode, DeviceWorkStatus workStatus,
        char* deviceDescription, QDateTime dateOfInstallation)
    : SurveillanceDevice(deviceCode, SurveillanceDeviceType::Cellular,
                       workStatus, deviceDescription, dateOfInstallation) {}
