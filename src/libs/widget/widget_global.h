#pragma once

#include <QtCore/qglobal.h>

#if defined(WIDGET_LIBRARY)
#  define WIDGET_EXPORT Q_DECL_EXPORT
#else
#  define WIDGET_EXPORT Q_DECL_IMPORT
#endif
