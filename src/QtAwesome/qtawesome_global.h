#ifndef QTAWESONME_GLOBAL_H
#define QTAWESONME_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef QTAWESONME_LIB
# define QTAWESONME_EXPORT Q_DECL_EXPORT
#else
# define QTAWESONME_EXPORT Q_DECL_IMPORT
#endif

#endif // QTAWESONME_GLOBAL_H