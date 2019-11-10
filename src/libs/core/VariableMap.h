// file: ./src/libs/core/VariableMap.h
#pragma once
#include "Core.h"

#include <QMap>
#include <QVariant>

#include "VariableId.h"


class CORE_EXPORT VariableMap
{
public:
    VariableMap(void);
    QVariant value(const VariableId & id) const
    { return mMap.value(id); }
    void set(const VariableId & id, const QVariant & var)
    { mMap.insert(id, var); }

private:
    QMap<VariableId, QVariant> mMap;
};

