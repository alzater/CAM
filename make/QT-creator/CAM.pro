QT += core
QT -= gui

CONFIG += c++11

TARGET = CAM
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../../src/core/main.cpp \
    ../../src/core/token.cpp \
    ../../src/core/solver.cpp \
    ../../src/core/tstr.cpp

HEADERS += \
    ../../src/core/token.h \
    ../../src/core/solver.h \
    ../../src/core/tstr.h
