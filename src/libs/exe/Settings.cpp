#include "Settings.h"

Settings::Settings(QObject * parent)
    : QSettings(parent)
{
    setObjectName("Settings");
}

void Settings::set(Settings::Key groupId, Settings::KeyValueList kvs)
{
    beginGroup(groupId);
    foreach (Settings::KeyValuePair keyValue, kvs)
        set(keyValue.first, keyValue.second);
    endGroup();
}

void Settings::set(Settings::Key &key, QVariant &var)
{
    QSettings::setValue(key, var);
    emit valueSet(key, var);
}
