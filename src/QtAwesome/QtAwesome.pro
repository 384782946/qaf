# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = lib
TARGET = QtAwesome
DESTDIR = ../../lib
QT += core widgets gui
CONFIG += debug_and_release
DEFINES += QT_DLL QTAWESONME_LIB
INCLUDEPATH += . \
    ./../Utils \
    ./debug \
    ./../../include \

#LIBS += -l$(NOINHERIT)
DEPENDPATH += .
CONFIG(debug,debug|release){
    win32:TARGET=$$join(TARGET,,,d)
    mac:TARGET=$$join(TARGET,,,_debug)
}

CONFIG(release,release|debug){

}
include(QtAwesome.pri)