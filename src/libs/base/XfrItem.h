// file: ./src/libs/XfrItem.h
#pragma once
#include "Base.h"

#include <QSharedDataPointer>

#include <QVariant>

#include "DataProperty.h"

#include "VersionInfo.h"

#define XFRITEM_DATAPROPS(TND) \
    TND(qint64, TimeStamp, 0) \
    TND(QtMsgType, MsgType, QtDebugMsg) \
/*  TND(FunctionInfo, Context, FunctionInfo()) */ \
    TND(QString, Message, "") \
    TND(QString, Format, "") \
    TND(QVariantList, Vars, QVariantList()) \
/*  TND(VersionInfo, Version, VersionInfo()) */ \
    TND(QVariantMap, Data, QVariantMap()) \


class XfrItemData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(XFRITEM_DATAPROPS)
public:
    XfrItemData(void)
    {
        DEFINE_DATAPROPS_CTORS(XFRITEM_DATAPROPS)
    }
};

class XfrItem
{
    DECLARE_PARENT_DATAPROPS(XFRITEM_DATAPROPS)
    DECLARE_DATAPROPS(XfrItem, XfrItemData)
    XfrItem(const QString message); // alternate ctor
};
