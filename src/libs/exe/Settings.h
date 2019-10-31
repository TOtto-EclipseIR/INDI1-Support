#ifndef SETTINGS_H
#define SETTINGS_H
#include "Exe.h"

#include <QObject>
#include <QSettings>

class EXE_EXPORT Settings : public QSettings
{
    Q_OBJECT
public:
    typedef QString Key;         // TODO BasicId
    typedef QVariant Value;
    typedef QPair<Key, Value> KeyValuePair;
    typedef QList<KeyValuePair> KeyValueList;

public:
    explicit Settings(QObject * parent=nullptr);
    QVariant value(const Key & key) const;
    bool contains(const Key & key) const;

public slots:
    void set(Key groupId, KeyValueList kvs);
    void set(Key & key, QVariant & var);


signals:
    void valueSet(Key key, QVariant var);

private:


};

#endif // SETTINGS_H
