TEMPLATE = app
TARGET= Test

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += quick widgets

SOURCES += \
    main.cpp \
    window.cpp \
    mainscreen.cpp \
    midireader.cpp \
    soundengine.cpp

unix: SOURCES += pianointerface_unix.cpp
else:win32: SOURCES += pianointerface_win.cpp

HEADERS += \
    window.h \
    mainscreen.h \
    midireader.h \
    soundengine.h

unix: HEADERS += pianointerface_unix.h
else:win32: HEADERS += pianointerface_win.h

unix|win32: LIBS += -L$$PWD/lib/ -lmidifile

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/midifile.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/lib/libmidifile.a

unix|win32: LIBS += -L$$PWD/lib/ -lsf2cute

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/sf2cute.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/lib/libsf2cute.a
