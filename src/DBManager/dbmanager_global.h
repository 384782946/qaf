﻿#ifndef DBMANAGER_GLOBAL_H
#define DBMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef DBMANAGER_LIB
# define DBMANAGER_EXPORT Q_DECL_EXPORT
#else
# define DBMANAGER_EXPORT Q_DECL_IMPORT
#endif

#endif // DBMANAGER_GLOBAL_H