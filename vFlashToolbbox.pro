QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ComStack/Com.cpp \
    ComStack/ComM.cpp \
    ComStack/Dcm.cpp \
    ComStack/Tp/tp.cpp \
    SDK/simulator.cpp \
    SDK/zlCAN.cpp \
    fileAddition.cpp \
    main.cpp \
    mainwindow.cpp \
    msg.cpp \
    trace.cpp

HEADERS += \
    ComStack/Com.h \
    ComStack/ComM.h \
    ComStack/Common/ComStack_Cfg.h \
    ComStack/Common/ComStack_Types.h \
    ComStack/Common/Compiler.h \
    ComStack/Common/Compiler_Cfg.h \
    ComStack/Common/Platform_Types.h \
    ComStack/Common/Std_Types.h \
    ComStack/Dcm.h \
    ComStack/Tp/tp.h \
    SDK/simulator.h \
    SDK/usb_can/ControlCAN.h \
    SDK/zlCAN.h \
    fileAddition.h \
    mainwindow.h \
    msg.h \
    trace.h

FORMS += \
    fileAddition.ui \
    mainwindow.ui \
    trace.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    SDK/usb_can/ControlCAN.dll \
    SDK/usb_can/ControlCAN.lib

RESOURCES += \
    img.qrc

unix|win32: LIBS += -L$$PWD/SDK/usb_can/ -lControlCAN

INCLUDEPATH += $$PWD/SDK/usb_can
DEPENDPATH += $$PWD/SDK/usb_can
