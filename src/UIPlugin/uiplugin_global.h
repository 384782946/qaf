#ifndef UIPLUGIN_GLOBAL_H
#define UIPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef UIPLUGIN_LIB
# define UIPLUGIN_EXPORT Q_DECL_EXPORT
#else
# define UIPLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // UIPLUGIN_GLOBAL_H
