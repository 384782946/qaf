#ifndef UTILS_GLOBAL_H
#define UTILS_GLOBAL_H

#include <qglobal.h>

#ifdef UTILS_LIB
# define UTILS_EXPORT Q_DECL_EXPORT
#else
# define UTILS_EXPORT Q_DECL_IMPORT
#endif

#endif // UTILS_GLOBAL_H