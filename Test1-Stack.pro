TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    basestack.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Stack.h \
    basestack.h

