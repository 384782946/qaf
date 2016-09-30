#ifndef LOG4QT_GLOBAL_H
#define LOG4QT_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LOG4QT_LIB
# define LOG4QT_EXPORT Q_DECL_EXPORT
#else
# define LOG4QT_EXPORT Q_DECL_IMPORT
#endif

#endif // LOG4QT_GLOBAL_H
