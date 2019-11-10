// file: ./src/libs/exe/ActionInfo2.h (trying VariableMap)
#pragma once
#include "Exe.h"

#include <QAction>

#include "../core/VariableId.h"
#include "../core/VariableMap.h"

class EXE_EXPORT ActionInfo2 : public VariableMap
{
public:
    ActionInfo2(const VariableId & name=VariableId());
    QAction * newAction(QObject * actionParent);

private:

};

