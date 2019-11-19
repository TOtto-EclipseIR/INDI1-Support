// file: ./src/libs/base/XfrFormat.h
#pragma once
#include "Base.h"

#include <QString>
#include <QVariant>

#include "FunctionInfo.h"


class XfrFormat : public QString // translator pattern
{
public:
    XfrFormat(void);
    XfrFormat(const QVariant & variant);
    XfrFormat(const QString & format,
              const QVariantList & vars);
    XfrFormat(const FunctionInfo context);
};

