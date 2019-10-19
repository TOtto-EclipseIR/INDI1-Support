#pragma once

#include <QtCore/qglobal.h>

#if defined(EXE_LIBRARY)
#  define EXE_EXPORT Q_DECL_EXPORT
#else
#  define EXE_EXPORT Q_DECL_IMPORT
#endif
