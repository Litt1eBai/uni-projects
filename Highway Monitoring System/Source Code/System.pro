QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cellularrecord.cpp \
    cellularrecordmodel.cpp \
    cellularrecordtableviewwidget.cpp \
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
    whereareyouwidget.cpp

HEADERS += \
    basicheader.h \
    cellularrecord.h \
    cellularrecordmodel.h \
    cellularrecordtableviewwidget.h \
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
    whereareyouwidget.h

FORMS += \
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
