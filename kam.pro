QT += core
QT -= gui

CONFIG += c++11

TARGET = kam
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    token.cpp \
    solver.cpp \
    tstr.cpp

HEADERS += \
    token.h \
    solver.h \
    tstr.h
