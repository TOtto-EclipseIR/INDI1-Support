// file: ./src/libs/exe/ActionInfo.h
#pragma once
#include "Exe.h"

#include <QSharedDataPointer>

#include <QAction>

#include "../base/DataProperty.h"
#include "../core/VariableId.h"
typedef QAction * PtrQAction;

#define ACTIONINFO_DATAPROPS(TND) \
    TND(VariableId, Name, VariableId()) \
    TND(QString, Text, QString()) \
    TND(QString, Menu, QString()) \
    TND(PtrQAction, Action, nullptr) \


class ActionInfoData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(ACTIONINFO_DATAPROPS)
public:
    LogItemData(void)
    {
        DEFINE_DATAPROPS_CTORS(ACTIONINFO_DATAPROPS)
    }
};

class EXE_EXPORT ActionInfo
{
    DECLARE_PARENT_DATAPROPS(ACTIONINFO_DATAPROPS)
    DECLARE_DATAPROPS(ActionInfo, ActionInfoData)
    ActionInfo(const VariableId & name); // alternate ctor
};



