QT -= gui
QT += multimedia

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/3rdparty/lame/lib/ -llibmp3lame

INCLUDEPATH += $$PWD/3rdparty/lame/include
DEPENDPATH += $$PWD/3rdparty/lame/include

HEADERS += \
    commandLineParser.h \
    lameEncoder.h \
    threadPool.h \
    wavFile.h \
    wavHeader.h

SOURCES += \
	commandLineParser.cpp \
    lameEncoder.cpp \
    main.cpp \
    threadPool.cpp \
    wavFile.cpp
