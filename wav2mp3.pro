QT -= gui
QT += multimedia

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/lame/libmp3lame/.libs/ -llibmp3lame

INCLUDEPATH += $$PWD/lame/include
DEPENDPATH += $$PWD/lame/include

HEADERS += \
    commandLineParser.h \
    threadPool.h \
    wavFile.h \
    wavHeader.h

SOURCES += \
        commandLineParser.cpp \
        main.cpp \
        threadPool.cpp \
        wavFile.cpp
