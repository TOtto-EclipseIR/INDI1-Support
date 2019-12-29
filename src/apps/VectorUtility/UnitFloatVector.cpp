#include "UnitFloatVector.h"

#include <QTextStream>

#include "Debug.h"

UnitFloatVector::UnitFloatVector(const int size)
{
    resize(size);
}

void UnitFloatVector::resize(const int size,
                             const UnitFloat value)
{
    mVector.fill(value, size);
}

void UnitFloatVector::setFromText(const QString vectorText,
                                  const int expectedSize)
{
    TRACEFN()
    UnitFloat::Value coef;
    QTextStream qts(vectorText.toLocal8Bit());
    mVector.clear();
    while ( ! qts.atEnd() && mVector.size() < expectedSize)
    {
        qts >> coef;
        mVector.append(coef);
    }
    TRACE << mVector.size();
}
