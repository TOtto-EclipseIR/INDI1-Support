// file: ./src/libs/exe/ActionInfo.h (trying VariableMap)
#pragma once
#include "Exe.h"

#include <QAction>
#include <QList>

#include "../core/VariableId.h"
#include "../core/VariableMap.h"

class EXE_EXPORT ActionInfo : public VariableMap
{
public:
    typedef QList<ActionInfo> List;
public:
    ActionInfo(const VariableId & name=VariableId());
    QAction * newAction(QObject * actionParent);
    QAction * action(void) const
    { return mpAction; }
    QString title(void) const;
    void debug(void) const;

private:
    QAction * mpAction=nullptr;
};

