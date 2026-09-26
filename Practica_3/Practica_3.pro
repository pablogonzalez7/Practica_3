TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bits.cpp \
        doc.cpp \
        lz78.cpp \
        main.cpp \
        rle.cpp

HEADERS += \
    bits.h \
    doc.h \
    lz78.h \
    rle.h
