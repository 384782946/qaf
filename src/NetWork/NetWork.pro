# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = NetWork

QT += core network
CONFIG += debug_and_release

include($$PWD/../Common.pri)

DESTDIR = $$PWD/../../output/lib/$$PLATFORM

DEFINES += QT_DLL NETWORK_LIB QT_NETWORK_LIB
INCLUDEPATH += . \
    $$PWD/../Utils

DEPENDPATH += $$PWD

include(NetWork.pri)
