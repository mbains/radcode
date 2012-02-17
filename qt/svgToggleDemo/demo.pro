TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
SOURCES += demo.cpp
include(../svgtoggle/svgtoggleswitch.pri)
QT += svg
RESOURCES += ../svgtoggle/svgtoggle.qrc
