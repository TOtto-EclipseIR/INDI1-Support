#pragma once

#include <QtCore/qglobal.h>

#if defined(MDI_LIBRARY)
#  define MDI_EXPORT Q_DECL_EXPORT
#else
#  define MDI_EXPORT Q_DECL_IMPORT
#endif
