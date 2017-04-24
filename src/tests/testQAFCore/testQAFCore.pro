#-------------------------------------------------
#
# Project created by QtCreator 2017-04-18T15:26:48
#
#-------------------------------------------------

TEMPLATE = app

QT       += testlib
QT       -= gui

TARGET = testqafcoretest
CONFIG   += debug_and_release console
CONFIG   -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += tst_testqafcoretest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

DEPENDPATH += $$PWD

win32:DESTDIR = $$PWD/../../../output/bin/win32
unix:DESTDIR = $$PWD/../../../output/bin/unix

INCLUDEPATH += $$PWD \
    $$PWD/../../QAFCore \
    $$PWD/../../Utils

LIBS += -L"$$PWD/../../../output/lib"

CONFIG(debug,debug|release){
    unix{
        TARGET=$$join(TARGET,,,_debug)
        LIBS += -lQtCommonModel_debug
    }
    else{
        TARGET=$$join(TARGET,,,d)
        LIBS += -lQAFCored
    }
}

CONFIG(release,release|debug){
    LIBS += -lQAFCore
}
