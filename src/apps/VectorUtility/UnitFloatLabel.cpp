#include "UnitFloatLabel.h"

qreal UnitFloatLabel::smEpsilon = 0.00001;

UnitFloatLabel::UnitFloatLabel(QWidget * parent)
    : QLabel(parent)
    , mUFV(0.0)
    , mFraction(0)
{

}

UnitFloatLabel::UnitFloatLabel(const UnitFloat value,
                               QWidget * parent)
    : QLabel(parent)
{
    set(value);
}

UnitFloatLabel::UnitFloatLabel(const UnitFloat value,
                               const QColor & baseColor,
                               QWidget * parent)
    : QLabel(parent)
    , mBaseColor(baseColor)
{
    set(value);
}

void UnitFloatLabel::set(const UnitFloat::Value ufv)
{
    mUFV = ufv;
    UnitFloat::Value auf = (ufv < 0.0) ? -ufv : ufv;
    mFraction = unsigned((auf - 1.0) * 10000000000.0);
}

void UnitFloatLabel::setUnitText(void)
{
    setText(formatUnit());
}

QString UnitFloatLabel::formatUnit(const int decimals,
                                   const bool forceSign)
{
    QString qst;
    if (forceSign) qst = sign();
    qst += QString::number(mFraction).left(decimals);
    return qst;
}

QChar UnitFloatLabel::sign(void)
{
    QChar qch(0x00B1); // &plusminus;
    if (mUFV < -getEpsilon())        qch = '-';
    else if (mUFV > getEpsilon())    qch = '+';
    return qch;
}

qreal UnitFloatLabel::getEpsilon()
{
    return smEpsilon;
}

void UnitFloatLabel::setEpsilon(const qreal &value)
{
    smEpsilon = value;
}
