TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    settings.cpp

HEADERS += \
    settings.h

OTHER_FILES += \
    sett.stg

