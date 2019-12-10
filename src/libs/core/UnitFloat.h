#pragma once
#include "Core.h"


class CORE_EXPORT UnitFloat
{
public:
    typedef qreal Value;
    typedef int Tier;

public:
    //UnitFloat(void) : mValue(Null), mTier(int(Null))  {}
    UnitFloat(const Value value) { set(value); }
    void set(const Value value);
    void clear(void);
    bool isValid(void) const;
    bool isNull(void) const;
    bool isZero(void) const;
    bool isPositive(void) const;
    bool isNegative(void) const;
    bool isUnderflow(void) const;
    bool isOverflow(void) const;
    QString toString(const int digits,
                     const int flags);
    Tier tier(void) const;

private:
    Value mValue;
    Tier mTier;

private:
    static Value Null;
    static Value Underflow;
    static Value Overflow;
};

