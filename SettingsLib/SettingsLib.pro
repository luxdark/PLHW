TEMPLATE = lib
CONFIG += shared
CONFIG -= qt

DEFINES += D_SHARED_LIB
SOURCES = settings.cpp
HEADERS = settings.h

TARGET = settings

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    sett.stg

