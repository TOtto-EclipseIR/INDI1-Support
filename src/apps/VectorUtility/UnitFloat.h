#pragma once

//#include <QVector>
#include "QQVector.h"


class UnitFloat
{
public:
    typedef qreal Value;
    typedef QQVector<Value> Vector;

public:
    UnitFloat(void) : mValue(smNull) {}
    UnitFloat(const Value realValue) { set(realValue); }
    void set(Value realValue,
             const bool validate=true);
    Value value(void) const { return  mValue; }
    operator Value (void) const { return value(); }
    QString toString(const int digits=4, const int options=0);
    operator QString(void) { return toString(); }
    bool isValid(void) const { return isValid(mValue); }

    static bool isValid(const Value value)
    { return (value > smMinimum && value < smMaximum); }

private:
    Value mValue=smInvalid;
    static Value smNull;
    static Value smInvalid;
    static Value smMinimum;
    static Value smMaximum;
};

