#pragma once

#include "UnitFloat.h"


class UnitFloatVector
{
public:
    UnitFloatVector(const int size=0);
    void resize(const int size,
                const UnitFloat value=UnitFloat());
    void set(const QVector<qreal> realVector);
    void setFromText(const QString vectorText,
                     const int expectedSize);
    int size(void) const { return mVector.size(); }
    UnitFloat::Value at(const int index) const;
    UnitFloat::Value operator [] (const int index) const
    { return at(index); }
    UnitFloat::Vector values(void) const
    { return mVector; }

private:
    UnitFloat::Vector mVector;
};

