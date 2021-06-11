#ifndef BASICHEADER_H
#define BASICHEADER_H

#include<QDateTime>

enum class SurveillanceDeviceType { CCTV = 0, Cellular, TrafficFlow, abstruct };
enum class DeviceWorkStatus { down = 0, running, notInstalled };
enum class Region { Chungking = 0, Shanghai, Canton };
enum class Colour { red = 0, blue, green, yellow, black, white, gray };
enum class VehicleType { military = 0, government, police, civilian };

//class DateTime {
//    int year, month, day;
//    int hour, min, sec;
//    void getSystemTime();
//    DateTime(int year, int month, int day, int hour, int min, int sec);
//    DateTime();
//};

//DateTime::DateTime(int year, int month, int day, int hour, int min, int sec)
//    : year(year), month(month), day(day), hour(hour), min(min), sec(sec) {}

//void DateTime::getSystemTime() {
//    QDateTime systemTime;
//    systemTime.currentDateTime();
//    this->year = systemTime.date().year();
//    this->month = systemTime.date().month();
//    this->day = systemTime.date().day();
//    this->hour = systemTime.time().hour();
//    this->min = systemTime.time().minute();
//    this->sec = systemTime.time().second();
//}

#endif // BASICHEADER_H
