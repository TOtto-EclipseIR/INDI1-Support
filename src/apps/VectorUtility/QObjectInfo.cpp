#include "QObjectInfo.h"

#include <QMetaEnum>
#include <QMetaObject>
#include <QObject>

#include "Debug.h"

QObjectInfo::QObjectInfo(QObject * object)
    : mpObject(object)
    , mpMetaObject(mpObject->metaObject())
{
    TRACE << Q_FUNC_INFO << object->objectName();
    for (int mx = 0; mx < mpMetaObject->enumeratorCount(); ++mx)
    {
        QMetaEnum qme = mpMetaObject->enumerator(mx);
        QString name = qme.name();
        mEnumNames << name;
        mEnums << qme;
        EnumItemMap itemMap = enumItemMap(qme);
        mMaps << itemMap;
    }
}

QStringList QObjectInfo::enumNames(void) const
{
    return mEnumNames;
}

int QObjectInfo::enumIndex(const QString &name) const
{
    for (int ix = 0; ix < mEnumNames.size(); ix++)
        if (mEnumNames.at(ix) == name)
            return ix;
    return -1;
}

QMetaEnum QObjectInfo::metaEnum(const int index) const
{
    return mEnums[index];
}

QMetaEnum QObjectInfo::metaEnum(const QString & name) const
{
    return mEnums[enumIndex(name)];
}

QStringList QObjectInfo::keys(const int enumIndex) const
{
    return keys(metaEnum(enumIndex));
}

QStringList QObjectInfo::keys(const QString &enumName) const
{
    return keys(metaEnum(enumName));
}

QObjectInfo::EnumItemMap QObjectInfo::items(const int index) const
{
    return enumItemMap(metaEnum(index));
}

QObjectInfo::EnumItemMap QObjectInfo::items(const QString &name) const
{
    return enumItemMap(metaEnum(name));
}

QStringList QObjectInfo::keys(const QMetaEnum &qme)
{
    int kk = qme.keyCount();
    QStringList ks;
    for (int kx = 0; kx < kk; kx++)
        ks << qme.key(kx);
    return ks;
}

QObjectInfo::EnumItemMap QObjectInfo::enumItemMap(const QMetaEnum &qme)
{
    EnumItemMap eim;
    foreach (QString k, keys(qme))
    {
        int v = qme.keyToValue(qPrintable(k));
        eim.insertUnique(k, v);
        // TRACE << k << v << QString::number(v, 16);
    }
    return eim;
}

