QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    cctvrecordmodel.cpp \
    cctvrecordtableviewwidget.cpp \
    cellularrecord.cpp \
    cellularrecordimportwindow.cpp \
    cellularrecordmodel.cpp \
    cellularrecordtableviewwidget.cpp \
    locationfilterproxymodel.cpp \
    main.cpp \
    mainwindow.cpp \
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
    record.cpp \
    statisticswidget.cpp \
    trafficrecord.cpp \
    trafficrecordmodel.cpp \
    whereareyouwidget.cpp

HEADERS += \
    basicheader.h \
    cctvrecord.h \
    cctvrecordmodel.h \
    cctvrecordtableviewwidget.h \
    cellularrecord.h \
    cellularrecordimportwindow.h \
    cellularrecordmodel.h \
    cellularrecordtableviewwidget.h \
    locationfilterproxymodel.h \
    mainwindow.h \
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
    record.h \
    statisticswidget.h \
    trafficrecord.h \
    trafficrecordmodel.h \
    whereareyouwidget.h

FORMS += \
    cctvrecordtableviewwidget.ui \
    cellularrecordimportwindow.ui \
    cellularrecordtableviewwidget.ui \
    mainwindow.ui \
    monitoreditwindow.ui \
    monitorsetupwindow.ui \
    monitortableviewwidget.ui \
    poleeditwindow.ui \
    polesetupwindow.ui \
    poletableviewwidget.ui \
    statisticswidget.ui \
    whereareyouwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pics.qrc
