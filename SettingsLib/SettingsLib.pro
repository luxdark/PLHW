TEMPLATE = lib
CONFIG += shared

DEFINES += D_SHARED_LIB
SOURCES = settings.cpp
HEADERS = settings.h

TARGET = settings
DLLDESTDIR = C:\workspace\bin
DESTDIR = C:\workspace\lib

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    sett.stg

