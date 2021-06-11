#include "cctvsurveillancedevice.h"
#include "basicHeader.h"

CCTVSurveillanceDevice::CCTVSurveillanceDevice() {
    this->deviceType = SurveillanceDeviceType::CCTV;
}
CCTVSurveillanceDevice::CCTVSurveillanceDevice(char* deviceCode) {
    strcpy(this->deviceCode, deviceCode);
}
CCTVSurveillanceDevice::CCTVSurveillanceDevice(
        char* deviceCode, DeviceWorkStatus workStatus,
        char* deviceDescription, QDateTime dateOfInstallation)
    : SurveillanceDevice(deviceCode, SurveillanceDeviceType::CCTV,
                       workStatus, deviceDescription, dateOfInstallation) {}
