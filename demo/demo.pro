QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = FHNotifier_demo
TEMPLATE = app
CONFIG += c++17 # needed for FramelessHelper

SOURCES += main.cpp \
            mainwindow.cpp

HEADERS += mainwindow.h

include(../framelesshelper/qmake/core.pri)
include(../framelesshelper/qmake/widgets.pri)

include(../FHNotifier.pri)

RESOURCES += \
    resources.qrc