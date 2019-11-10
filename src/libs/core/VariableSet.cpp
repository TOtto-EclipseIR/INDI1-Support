#include "VariableSet.h"

#include <QByteArray>
#include <QList>
#include <QMap>
#include <QVariant>

#include "VariableIdList.h"

VariableSetData::VariableSetData(const VariableSetData & other)
    : QSharedData(other)
    , mName(other.mName)
    , mUllKey(other.mUllKey)
    , mId(other.mId)
    , mIdVariantMap(other.mIdVariantMap)
    , mVariantList(other.mVariantList)
    , mBytes(other.mBytes)
{
}


VariableSet::VariableSet(const QString & name)
    : data(new VariableSetData)
{
    data->mName = name;
}

VariableSet::VariableSet(const quint64 key,
            const QString & id,
            const QString & name)
    : data(new VariableSetData)
{
    data->mName = name;
    data->mUllKey = key;
    data->mId = id;
}

VariableSet::VariableSet(const VariableSet & other)
    : data(other.data)
{
}

VariableSet &VariableSet::operator=(const VariableSet & rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

VariableSet::~VariableSet()
{
}

QString VariableSet::name(void) const
{
    return data->mName;
}

quint64 VariableSet::key(void) const
{
    return data->mUllKey;
}

QString VariableSet::id(void) const
{
    return data->mId;
}

void VariableSet::setName(const QString & newName)
{
    data->mName = newName;
}

void VariableSet::setKey(const quint64 key)
{
    data->mUllKey = key;
}

void VariableSet::setId(const QString & id)
{
    data->mId = id;
}

void VariableSet::clear(void)
{
    data->mIdVariantMap.clear();
    data->mVariantList.clear();
    data->mBytes.clear();
}

int VariableSet::binarySize(void) const
{
    return data->mBytes.size();
}

int VariableSet::listSize(void) const
{
    return data->mVariantList.size();
}

int VariableSet::mapSize(void) const
{
    return data->mIdVariantMap.size();
}

bool VariableSet::contains(const VariableId & vid) const
{
    return data->mIdVariantMap.contains(vid.sortable());
}

void VariableSet::reset(void)
{
    foreach (QString key, data->mIdVariantMap.keys())
        data->mIdVariantMap[key].reset();
}

/** @fn blog()
  *
  * @todo Stringify QVariants
  */
void VariableSet::blog(void) const
{
#if 0
    BLOG(Severity::Dump, "VariableSet: name=%s, key=%d 0x%X, id=%s",
         qPrintable(data->name_s), data->key_u64,
         data->key_u64, qPrintable(data->id_s));
    foreach (QString key, data->vbl_map.keys())
    {
        Variable vbl(data->vbl_map.value(key));
        BLOG(Severity::Dump, "%s = {%s}",
             qPrintable(vbl.id()), qPrintable(vbl.var().toString()));
    }
    for (int x = 0; x < data->var_list.size(); ++x)
        BLOG(Severity::Dump, "%i. {%s}", x,
             qPrintable(data->var_list.at(x).toString()));
    BLOG(Severity::Dump, "%d bytes of Binary", data->_ba.size());
#endif
}


bool VariableSet::isEmpty(void) const
{
    return data->mIdVariantMap.isEmpty()
                && data->mVariantList.isEmpty()
                && data->mBytes.isEmpty();
}

void VariableSet::set(const QVariantList & vl)
{
    data->mVariantList = vl;
}

void VariableSet::set(const Variable & vbl)
{
    data->mIdVariantMap[vbl.id().sortable()] = vbl;
}

void VariableSet::set(const Variable::List & vbls)
{
    foreach (Variable vbl, vbls)
        set(vbl);
}

void VariableSet::set(const VariableId & vid,
                      const QVariant & value)
{
    QVariant def(data->mIdVariantMap[vid.sortable()].defaultVar());
    data->mIdVariantMap[vid.sortable()] = Variable(vid, value, def);
}

void VariableSet::set(const int index,
                      const QVariant & value)
{
    while (data->mVariantList.size() <= index)
        data->mVariantList.append(QVariant());
    data->mVariantList[index] = value;
}

void VariableSet::set(const QByteArray & ba)
{
    data->mBytes = ba;
}

void VariableSet::reset(const VariableId & id)
{
    if (data->mIdVariantMap.contains(id.sortable()))
        data->mIdVariantMap[id.sortable()].reset();
}

void VariableSet::append(const QVariant & value)
{
    data->mVariantList.append(value);
}

Variable VariableSet::at(const VariableId & id) const
{
    return data->mIdVariantMap.value(id.sortable());
}

QVariant VariableSet::value(const VariableId & id,
                            const QVariant &defaultValue) const
{
#if 1 // def QT_DEBUG
    QString key(id.sortable());
    if (data->mIdVariantMap.contains(key))
    {
        Variable vbl(data->mIdVariantMap.value(key));
        QVariant var(vbl.var());
        return var;
    }
    else
        return defaultValue;
#else
    return data->vbl_map.value(id.sortable()).var();
#endif
}

QVariant VariableSet::value(const int index) const
{
    return (index >= 0 && index < data->mVariantList.size())
            ? data->mVariantList.at(index)
            : QVariant();
}

QByteArray VariableSet::value(void) const
{
    return data->mBytes;
}

QVariantList VariableSet::values(void) const
{
    return data->mVariantList;
}


VariableSet VariableSet::exportSection(const VariableId & sectionId) const
{
    VariableSet result;
    int n = sectionId.sectionCount();
    foreach (VariableId vid, ids(sectionId))
    {
            VariableId newId(vid.sections(n));
            result.set(newId, value(vid));
    }
    return result;
}

VariableIdList VariableSet::ids(const VariableId & within) const
{
    VariableIdList result;
    if (within.isNull())
        foreach (Variable vbl, data->mIdVariantMap.values())
            result.append(vbl.id());
    else
    {
        QString prefix(within.sortable());
        foreach (Variable vbl, data->mIdVariantMap.values())
            if (vbl.id().sortable().startsWith(prefix))
                result.append(vbl.id());
    }
    return result;
}

VariableIdList VariableSet::sectionIds(const VariableId & within) const
{
    VariableIdList result;
    if (within.isNull())
        foreach (Variable vbl, data->mIdVariantMap.values())
        {
            QString section(vbl.id().section(0));
            if ( ! result.contains(VariableId(section)))
                result.append(VariableId(section));
        }
    else
    {
        int n = within.sectionCount();
        foreach (Variable vbl, data->mIdVariantMap.values())
        {
            QString section(vbl.id().section(n));
            if (QString(within) == vbl.id().sections(0, n-1))
                if ( ! result.contains(VariableId(section)))
                    result.append(VariableId(section));
        }
    }
    return result;
}

void VariableSet::import(const VariableSet & other,
                         const VariableId & sectionId)
{
    foreach (Variable vbl, other.data->mIdVariantMap.values())
    {
        VariableId vid(vbl.id());
        vid.prepend(sectionId);
        set(vid, vbl.var());
    }
}

Variable::List VariableSet::all(void) const
{
    return data->mIdVariantMap.values();
}
