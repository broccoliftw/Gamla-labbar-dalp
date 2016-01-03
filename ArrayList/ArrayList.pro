TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    listclient.cpp \
    ArrayList.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    ArrayList.h
