#ifndef BASICHEADER_H
#define BASICHEADER_H


const int c_IMEIDigit = 16;
const int c_DeviceCodeDiget = 12;
const int c_PoleCodeDigit = 8;
const int c_recordCodeDigit = 10;
const int c_DescriptionLength = 100;

enum class MonitorDeviceType { CCTV = 0, Cellular, TrafficFlow, Abstract };
enum class DeviceWorkStatus { Running = 0, Down, NotInstalled };
enum class Region { Chungking = 0, Shanghai, Canton };
enum class Colour { Red = 0, Blue, Green, Yellow, Black, White, Gray };
enum class VehicleType { Military = 0, Government, Police, Civilian };


#endif // BASICHEADER_H
