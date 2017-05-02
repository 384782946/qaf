# 定义一些变量或功能，请在pro的CONFIG配置之后包含该文件
# 用法：include(Common.pri)

#defineReplace(qtLibraryName) {
#   unset(LIBRARY_NAME)
#   LIBRARY_NAME = $$1
#   CONFIG(debug, debug|release) {
#      !debug_and_release|build_pass {
#          mac:RET = $$member(LIBRARY_NAME, 0)_debug
#              else:win32:RET = $$member(LIBRARY_NAME, 0)d
#      }
#   }
#   isEmpty(RET):RET = $$LIBRARY_NAME
#   return($$RET)
#}

#定义平台名
contains(QT_ARCH, i386): ARCHITECTURE = x86
else: ARCHITECTURE = $$QT_ARCH

macx: PLATFORM = "mac"
else:win32: PLATFORM = "win32"
else:linux-*: PLATFORM = "linux-$${ARCHITECTURE}"
else: PLATFORM = "unknown"

#定义工程生成目录
PROJECT_LIBDIR = $$PWD/../output/lib/$$PLATFORM
PROJECT_BINDIR = $$PWD/../output/bin/$$PLATFORM

#指定依赖路径
DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

#指定库依赖路径
LIBS += -L"$$PROJECT_LIBDIR"

#指定生成目标名
TARGET = $$qtLibraryTarget($$TARGET)

#指定生成路径
contains(TEMPLATE, .*lib){
    DESTDIR = $$PROJECT_LIBDIR

    win32{
        DLLDESTDIR = $$PROJECT_BINDIR
        QMAKE_DISTCLEAN += $$PROJECT_BINDIR/$${TARGET}.dll
    }
}
else{
    DESTDIR = $$PROJECT_BINDIR
}


#添加库依赖
TEMPLATE += fakelib

for(lib, QAF_LIBS) {
    LIBS += -l$$qtLibraryTarget($$lib)
}

TEMPLATE -= fakelib
