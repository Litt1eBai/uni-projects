QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cctvrecord.cpp \
    cctvsurveillancedevice.cpp \
    cellularrecord.cpp \
    cellularsurveillancedevice.cpp \
    highwaypole.cpp \
    main.cpp \
    mainwindow.cpp \
    record.cpp \
    surveillancedevice.cpp \
    trafficflowrecord.cpp \
    trafficflowsurveillancedevice.cpp

HEADERS += \
    basicHeader.h \
    cctvrecord.h \
    cctvsurveillancedevice.h \
    cellularrecord.h \
    cellularsurveillancedevice.h \
    highwaypole.h \
    mainwindow.h \
    record.h \
    surveillancedevice.h \
    trafficflowrecord.h \
    trafficflowsurveillancedevice.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource_icon.qrc
