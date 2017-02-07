TEMPLATE = app
TARGET= Test

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += quick widgets

SOURCES += \
    main.cpp \
    window.cpp \
    pianointerface.cpp \
    mainscreen.cpp \
    midireader.cpp

HEADERS += \
    window.h \
    pianointerface.h \
    mainscreen.h \
    midireader.h

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../midifile/lib/release/ -lmidifile
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../midifile/lib/debug/ -lmidifile
else:unix: LIBS += -L$$PWD/../../midifile/lib/ -lmidifile

INCLUDEPATH += $$PWD/../../midifile/include
DEPENDPATH += $$PWD/../../midifile/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../midifile/lib/release/libmidifile.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../midifile/lib/debug/libmidifile.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../midifile/lib/release/midifile.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../midifile/lib/debug/midifile.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../midifile/lib/libmidifile.a
