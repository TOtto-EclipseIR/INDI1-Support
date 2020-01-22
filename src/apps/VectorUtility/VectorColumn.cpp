// File: VectorColumn.cpp

#include "VectorColumn.h"

#include "Debug.h"
#include "VectorObject.h"

VectorColumn::VectorColumn(void)
    : cmRows(0)
    , cmInvalid(qQNaN())
{;}

VectorColumn::VectorColumn(const Column col,
                           const int rows)
    : VectorColumnRole(col)
    , cmRows(rows)
    , cmInvalid(qQNaN())
{
    TRACEQFI << columnName() << cmRows;
    clear();
}

VectorColumn::VectorColumn(const Column col,
                           const UnitFloatVector & values)
    : VectorColumnRole(col)
    , cmRows(values.size())
    , cmInvalid(qQNaN())
{
    TRACEQFI << columnName() << cmRows;
    set(values);
}

void VectorColumn::clear(void)
{
    TRACEFN()
    mValues.fill(cmInvalid, cmRows);
}

void VectorColumn::set(const VectorColumn & other)
{
    TRACEFN()
//    WEXPECTEQ(role(), other.role());
    mValues = other.values();
    mBaseColors = other.mBaseColors;
    WANTDO("access functions");
}

void VectorColumn::set(VectorColumn::ValueVector values)
{
    TRACEQFI << columnName() << cmRows;
    clear();
    values.resize(cmRows);
    mValues = values;
}

void VectorColumn::set(UnitFloatVector ufv)
{
    TRACEQFI << columnName() << rows();
    ufv.resize(rows());
    ValueVector vv;
    foreach (Value v, vv) vv.append(v);
}

void VectorColumn::set(VectorObject * vector)
{
    TRACEQFI << columnName() << cmRows;
    set(vector->coefVector().values());
}

void VectorColumn::set(const ForeBackGroundColors & fbgc)
{
    WANTUSE(fbgc);
    WANTDO("implimenmt");
}

VectorColumn VectorColumn::setDelta(const VectorColumn &vcMinuend,
                                    const VectorColumn &vcSubtrahend)
{
    NEEDUSE(vcMinuend) NEEDUSE(vcSubtrahend) NEEDRTN(*this)

}

VectorColumn VectorColumn::setRatio(const VectorColumn &vcDividend,
                                    const VectorColumn &vcDivisor)
{
    NEEDUSE(vcDividend) NEEDUSE(vcDivisor) NEEDRTN(*this)
}

bool VectorColumn::isEmpty(void) const
{
    TRACEFN()
    return mValues.isEmpty() | mValues.contains(cmInvalid);
}

bool VectorColumn::isValid(void) const
{
    TRACEFN()
    return (mValues.size() == cmRows)
            && ! mValues.contains(cmInvalid);
}
