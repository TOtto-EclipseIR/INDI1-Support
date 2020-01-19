#include "UnitFloatVector.h"

#include <QTextStream>

#include "Debug.h"

UnitFloatVector::UnitFloatVector(const int size)
{
    TRACEQFI << size;
    resize(size);
}

void UnitFloatVector::resize(const int size,
                             const UnitFloat value)
{
    TRACEQFI << size << value;
    if (value.isValid())
        mVector.fill(value, size);
    else
        mVector.resize(size);
    TRACEQFI << "result : " << mVector.size() << mVector.first() << mVector.last();
}

void UnitFloatVector::setFromText(const QString vectorText,
                                  const int expectedSize)
{
    TRACEQFI << vectorText.size() << expectedSize;
    TRACE << vectorText.left(100);
    TRACE << vectorText.right(100);
    mVector.clear();
    mVector.reserve(expectedSize);
#if 1
    QStringList qsl = vectorText.simplified()
                                .split(' ', QString::KeepEmptyParts);
//    TRACE << qsl;
    while ( ! qsl.isEmpty() && mVector.size() < expectedSize)
    {
        QString s = qsl.takeFirst();
        UnitFloat::Value d = s.toDouble();
        mVector.append(d);
    //    TRACE << s << d << qsl.size() << mVector.size();
    }
        // mVector.append(qsl.takeFirst().toDouble());
#else
    UnitFloat::Value coef;
    QTextStream qts(vectorText.toLocal8Bit());
    TRACE << qts.status();
    while ( ! qts.atEnd() && mVector.size() < expectedSize)
    {
        qts >> coef;
        mVector.append(coef);
        TRACE << qts.status() << mVector.size() << coef;
    }
#endif
//    TRACE << mVector.size() << mVector;
}

UnitFloat::Value UnitFloatVector::value(const int index) const
{
//    TRACEQFI << index << mVector.at(index);
    return mVector.at(index);
}

UnitFloat::Value & UnitFloatVector::at(const int index)
{
//    TRACEQFI << index << mVector.at(index);
    return mVector[index];
}
