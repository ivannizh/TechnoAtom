TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

HEADERS += \
    myvector.h

unix:!macx: LIBS += -lgtest

unix:!macx: LIBS += -lpthread
