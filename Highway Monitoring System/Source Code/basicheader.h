#ifndef BASICHEADER_H
#define BASICHEADER_H

#include <QString>
#include <QDir>
#include <string>

const int c_IMEIDigit = 16;
const int c_DeviceCodeDiget = 12;
const int c_PoleCodeDigit = 8;
const int c_recordCodeDigit = 10;
const int c_DescriptionLength = 100;
const int c_VehicleRegistrationNoLength = 16;
const int c_filePathLength = 100;

enum class MonitorDeviceType { CCTV = 0, Cellular, TrafficFlow, Abstract };
enum class DeviceWorkStatus { Running = 0, Down, NotInstalled };
//enum class Region { CQ = 0, SH, GD };
//enum class Colour { Red = 0, Blue, Green, Yellow, Black, White, Gray };
//enum class VehicleType { Military = 0, Government, Police, Civilian };

//QString rootFolder_filePath = "C:\\MonitorSystem\\";
//QString poleData_filePath = rootFolder_filePath + "poleData.dat";
//QString monitorData_filePath = rootFolder_filePath + "monitorData.dat";
//QString trafficRecord_filePath = rootFolder_filePath + "trafficData.dat";
//QString cellularRecord_filePath = rootFolder_filePath + "cellularData.dat";
//QString cctvRecord_filePath = rootFolder_filePath + "cctvData.dat";


//void createRootPath() {
//    QDir dir(rootFolder_filePath);
//    if (!dir.exists()) {
//        dir.mkpath(rootFolder_filePath);
//    }
//}


#endif // BASICHEADER_H
