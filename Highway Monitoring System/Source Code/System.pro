QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./QXlsx/         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./QXlsx/header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./QXlsx/source/  # current QXlsx source path is ./source/
include(./QXlsx/QXlsx.pri)


SOURCES += \
    cctvrecord.cpp \
    cctvrecorddisplaywidget.cpp \
    cctvrecordimportwindow.cpp \
    cctvrecordmodel.cpp \
    cctvrecordproxymodel.cpp \
    cctvrecordtableviewwidget.cpp \
    cellularrecord.cpp \
    cellularrecordcurvewidget.cpp \
    cellularrecordimportwindow.cpp \
    cellularrecordmodel.cpp \
    cellularrecordproxymodel.cpp \
    cellularrecordtableviewwidget.cpp \
    dashboardwidget.cpp \
    locationfilterproxymodel.cpp \
    main.cpp \
    mainwindow.cpp \
    mediaplayer.cpp \
    monitor.cpp \
    monitoreditwindow.cpp \
    monitormodel.cpp \
    monitorsetupwindow.cpp \
    monitortableviewwidget.cpp \
    pole.cpp \
    poleeditwindow.cpp \
    polemodel.cpp \
    polesetupwindow.cpp \
    poletableviewwidget.cpp \
    qcustomplot.cpp \
    record.cpp \
    statisticswidget.cpp \
    trafficrecord.cpp \
    trafficrecordcurvewidget.cpp \
    trafficrecordimportwindow.cpp \
    trafficrecordmodel.cpp \
    trafficrecordproxymodel.cpp \
    trafficrecordtableviewwidget.cpp \
    whereareyouwidget.cpp

HEADERS += \
    basicheader.h \
    cctvrecord.h \
    cctvrecorddisplaywidget.h \
    cctvrecordimportwindow.h \
    cctvrecordmodel.h \
    cctvrecordproxymodel.h \
    cctvrecordtableviewwidget.h \
    cellularrecord.h \
    cellularrecordcurvewidget.h \
    cellularrecordimportwindow.h \
    cellularrecordmodel.h \
    cellularrecordproxymodel.h \
    cellularrecordtableviewwidget.h \
    dashboardwidget.h \
    locationfilterproxymodel.h \
    mainwindow.h \
    mediaplayer.h \
    monitor.h \
    monitoreditwindow.h \
    monitormodel.h \
    monitorsetupwindow.h \
    monitortableviewwidget.h \
    pole.h \
    poleeditwindow.h \
    polemodel.h \
    polesetupwindow.h \
    poletableviewwidget.h \
    qcustomplot.h \
    record.h \
    statisticswidget.h \
    trafficrecord.h \
    trafficrecordcurvewidget.h \
    trafficrecordimportwindow.h \
    trafficrecordmodel.h \
    trafficrecordproxymodel.h \
    trafficrecordtableviewwidget.h \
    whereareyouwidget.h

FORMS += \
    cctvrecorddisplaywidget.ui \
    cctvrecordimportwindow.ui \
    cctvrecordtableviewwidget.ui \
    cellularrecordcurvewidget.ui \
    cellularrecordimportwindow.ui \
    cellularrecordtableviewwidget.ui \
    dashboardwidget.ui \
    mainwindow.ui \
    mediaplayer.ui \
    monitoreditwindow.ui \
    monitorsetupwindow.ui \
    monitortableviewwidget.ui \
    poleeditwindow.ui \
    polesetupwindow.ui \
    poletableviewwidget.ui \
    statisticswidget.ui \
    trafficrecordcurvewidget.ui \
    trafficrecordimportwindow.ui \
    trafficrecordtableviewwidget.ui \
    whereareyouwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc
