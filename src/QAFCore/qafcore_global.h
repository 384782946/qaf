#ifndef QAFCORE_GLOBAL_H
#define QAFCORE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef QAFCORE_LIB
# define QAFCORE_EXPORT Q_DECL_EXPORT
#else
# define QAFCORE_EXPORT Q_DECL_IMPORT
#endif

#endif // QAFCORE_GLOBAL_H