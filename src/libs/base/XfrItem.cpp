#include "XfrItem.h"

#include <QDateTime>

DEFINE_DATAPROPS(XfrItem, XfrItemData)

void XfrItem::ctor(void) // common ctor behavior
{
    setTimeStamp(QDateTime::currentMSecsSinceEpoch());
}

void XfrItem::dtor(void) {} // ditto dtor
