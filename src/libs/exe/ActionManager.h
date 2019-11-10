#pragma once
#include "Exe.h"

#include <QObject>

#include<QString>
class QAction;
class QMenu;

#include "../core/VariableSet.h"

#include "ActionInfo2.h"

typedef QMap<QString, QMenu *> NameMenuMap;
typedef QMap<QString, ActionInfo2> NameActionInfoMap;

class EXE_EXPORT ActionManager : public QObject
{
    Q_OBJECT
public:
    explicit ActionManager(QObject * parent=nullptr);
    void configure(const VariableSet & actionConfig);
    ActionInfo2 actionInfo(const VariableId name) const
    { return mNameActionInfoMap.value(name); }

public slots:


signals:

private:
    NameActionInfoMap mNameActionInfoMap;
};

