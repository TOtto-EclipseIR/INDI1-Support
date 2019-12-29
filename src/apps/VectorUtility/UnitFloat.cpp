#include "UnitFloat.h"

UnitFloat::Value UnitFloat::smNull = -999.9;
UnitFloat::Value UnitFloat::smInvalid = +999.9;
UnitFloat::Value UnitFloat::smMinimum = -1.0;
UnitFloat::Value UnitFloat::smMaximum = +1.0;

void UnitFloat::set(UnitFloat::Value value,
                    const bool validate)
{
    if (validate && ! isValid(value)) value = smInvalid;
    mValue = value;
}

QString UnitFloat::toString(const int digits,
                            const int options)
{
    (void)(options);
    Value absValue = abs(mValue);
    QString absString = QString::number(absValue, 'F', digits);
    QChar sign(0x00B1); // &PlusMinus;
    if (mValue < 0.00)      sign = '-';
    else if (mValue > 0.0)  sign = '+';
    if (isValid())
    {
        absString = QString::number(absValue,
                        'F', digits+2).mid(2, digits);
    }
    return sign+absString;
}
