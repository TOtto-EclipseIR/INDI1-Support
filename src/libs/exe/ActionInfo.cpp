#include "ActionInfo.h"

DEFINE_DATAPROPS(ActionInfo, ActionInfoData)

ActionInfo::ActionInfo(const VariableId & name) // alternate
    : data(new ActionInfoData)
{
    ctor();
    setName(name);
}

void ActionInfo::ctor(void) {}
void ActionInfo::dtor(void) {}

