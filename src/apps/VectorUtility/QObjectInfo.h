#pragma once

class QObject;

#include <QList>
#include <QMap>
#include <QMetaEnum>
#include <QMetaObject>
#include <QString>
#include <QStringList>

#include "DualMap.h"

class QObjectInfo
{
public:
    typedef QPair<QString, int> EnumItem;
    typedef QList<EnumItem> EnumItemList;
    typedef QList<QMetaEnum> MetaEnumList;
    typedef DualMap<QString, int> EnumItemMap;
    typedef QMap<QString, EnumItemMap> ItemMapMap;
    typedef QList<EnumItemMap> EnumItemMaps;

public:
    QObjectInfo(QObject * object);
    QStringList enumNames(void) const;
    int enumIndex(const QString & name) const;
    QMetaEnum metaEnum(const int index) const;
    QMetaEnum metaEnum(const QString & name) const;
    QStringList keys(const int enumIndex) const;
    QStringList keys(const QString & enumName) const;
    EnumItemMap items(const int index) const;
    EnumItemMap items(const QString & name) const;

protected:
    static QStringList keys(const QMetaEnum & qme);
    static EnumItemMap enumItemMap(const QMetaEnum & qme);

private:
    QObject * mpObject=nullptr;
    const QMetaObject * mpMetaObject=nullptr;
    QStringList mEnumNames;
    MetaEnumList mEnums;
    EnumItemMaps mMaps;
};

