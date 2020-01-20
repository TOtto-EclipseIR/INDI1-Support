#include "VectorColumnTwig.h"

#include "Debug.h"

VectorColumnTwig::VectorColumnTwig(void)
    : QTableWidgetItem(userNull)
    , cmType(userNull)
{
    TRACEFN()
}

VectorColumnTwig::VectorColumnTwig(const ItemType type)
    : QTableWidgetItem(type)
    , cmType(type)
{
    TRACEFN()

}

VectorColumnTwig::VectorColumnTwig(const QString text,
                                   const ItemType type)
    : QTableWidgetItem(text, type)
    , cmType(type)
    , mText(text)
    , mInt(text.toInt())
    , mReal(text.toDouble())

{
    TRACEQFI << mText;
    setText(mText);
}

VectorColumnTwig::VectorColumnTwig(const int iValue,
                                   const ItemType type)
    : QTableWidgetItem(QString::number(iValue), type)
    , cmType(type)
    , mText(text())
    , mInt(iValue)
    , mReal(qreal(iValue))
{
    // TRACEQFI << mText;
}

VectorColumnTwig::VectorColumnTwig(const qreal rValue,
                                   const ItemType type)
    : QTableWidgetItem(QString::number(rValue), type)
    , cmType(type)
    , mText(QString::number(rValue))
    , mInt(int(rValue))
    , mReal(rValue)
{
    // TRACEQFI << mText;
    setText(mText);
}

VectorColumnTwig * VectorColumnTwig::clone() const
{
    return (VectorColumnTwig *)(QTableWidgetItem::clone());
}

QFont VectorColumnTwig::font()
{
    return QFont(mParms.value("FontFamily", "Courier").toString(),
                 mParms.value("FontPoints", 12).toInt());
}

VectorColumnTwig::ItemType
    VectorColumnTwig::typeFor(const VectorColumnRole::Column col)
{
    ItemType it = userNull;
    switch (col)
    {
    case VectorColumnRole::BaselineCol:
    case VectorColumnRole::SubjectOneCol:
    case VectorColumnRole::SubjectTwoCol:
        it = UnitType;
        break;

    case VectorColumnRole::DeltaBaseOneCol:
    case VectorColumnRole::DeltaBaseTwoCol:
    case VectorColumnRole::DeltaOneTwoCol:
        it = DeltaType;
        break;

    case VectorColumnRole::RatioBaseOneCol:
    case VectorColumnRole::RatioBaseTwoCol:
    case VectorColumnRole::RatioOneTwoCol:
        it = RatioType;
        break;

    default:
        WARNQFI << "Invalid Role:" << col;
        break;
    }
    return it;
}


VectorColumnTwig::Parms::Parms(const QVariantMap & settings)
{
    TRACEFN()
    set(settings);
}

void VectorColumnTwig::Parms::set(const QVariantMap & settings)
{
    TRACEFN()
    mSettings = settings;
}

void VectorColumnTwig::Parms::replace(const QString & key,
                                     const QVariant & setting)
{
    TRACEQFI << key << setting;
    mSettings.insert(key, setting);
}

void VectorColumnTwig::Parms::replace(const QVariantMap & settings)
{
    TRACEFN()
    foreach(QString key, settings.keys())
            replace(key, settings.value(key));
}

QVariant VectorColumnTwig::Parms::value(const QString & key,
                                const QVariant & defValue) const
{
    QVariant var = mSettings.value(key, defValue);
//    TRACEQFI << key << var;
    return var;
}

