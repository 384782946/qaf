#ifndef NETWORK_GLOBAL_H
#define NETWORK_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef NETWORK_LIB
# define NETWORK_EXPORT Q_DECL_EXPORT
#else
# define NETWORK_EXPORT Q_DECL_IMPORT
#endif

#endif // NETWORK_GLOBAL_H
