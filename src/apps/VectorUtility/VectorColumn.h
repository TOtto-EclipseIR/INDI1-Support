// File: VectorColumn.h
#pragma once

#include <QColor>
#include <QVector>


#include "BaseColorSet.h"
#include "UnitFloat.h"
#include "UnitFloatVector.h"
#include "Vector.h"
#include "VectorColumnRole.h"
class VectorObject;


class VectorColumn : public VectorColumnRole
{
public:
    typedef qreal Value;
    typedef QVector<Value> ValueVector;

public:
    VectorColumn(void);
    VectorColumn(const Column col, const int rows);
    VectorColumn(const Column col,
                 const UnitFloatVector & values);
    void clear(void);
    void set(const VectorColumn & other);
    void set(ValueVector values);
    void set(UnitFloatVector ufv);
    void set(VectorObject * vector);
    void set(const ForeBackGroundColors &fbgc);
    VectorColumn setDelta(const VectorColumn & vcMinuend,
                          const VectorColumn & vcSubtrahend);
    VectorColumn setRatio(const VectorColumn & vcDividend,
                          const VectorColumn & vcDivisor);

    bool isEmpty(void) const;
    bool isValid(void) const;
    ValueVector values(void) const
    { return mValues; }
    ValueVector & values(void)
    { return mValues; }
    int rows(void) const
    { return cmRows; }
    bool operator ==(const VectorColumn & other);
    bool operator <(const VectorColumn & other);
    //void operator =(const VectorColumn & other);
    QColor baseBackgroundColor(void) const
    { return  mBaseColors.second; }

public: // static

private:
    const int cmRows;
    const Value cmInvalid;
    ForeBackGroundColors mBaseColors;
    ValueVector mValues;

private: // static
};

