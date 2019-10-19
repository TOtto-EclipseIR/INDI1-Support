#pragma once

#include <QtCore/qglobal.h>

#if defined(VECTOR_LIBRARY)
#  define VECTOR_EXPORT Q_DECL_EXPORT
#else
#  define VECTOR_EXPORT Q_DECL_IMPORT
#endif
