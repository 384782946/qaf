# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = QAFCore
DESTDIR = ../../lib
QT += core xml widgets gui
CONFIG += debug_and_release
DEFINES += QT_DLL QAFCORE_LIB QT_WIDGETS_LIB QT_XML_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug \
    ./../QtAwesome \
    ./../Utils \
    ./../QtCommonModel
LIBS += -L"./../../lib"
DEPENDPATH += .
CONFIG(debug,debug|release){
    win32:TARGET=$$join(TARGET,,,d)
    mac:TARGET=$$join(TARGET,,,_debug)

    LIBS += -lQtCommonModeld
}

CONFIG(release,release|debug){
    LIBS += -lQtCommonModel
}
include(QAFCore.pri)