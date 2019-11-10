#include "ActionManager.h"

#include <QMenu>

#include "../core/VariableIdList.h"

#include "ActionInfo2.h"

ActionManager::ActionManager(QObject * parent)
    : QObject(parent)
{
    setObjectName("ActionManager");
}

void ActionManager::configure(const VariableSet & config,
                              NameMenuMap * nameMenus)
{
    VariableIdList ids = config.sectionIds(); // unique
    foreach (VariableId actionName, ids)
    {
        ActionInfo2 ai(actionName);
        VariableSet actionConfig = config.exportSection(actionName);
        foreach (VariableId id, actionConfig.ids())
        {
            QVariant var = actionConfig.value(id);
            ai.set(id, var);
        }
        QAction * action = ai.newAction(this);
        mNameActionMap.insert(actionName, action);
        if (nameMenus)
            nameMenus->value(ai.value("Menu").toString())
                     ->addAction(action);
    }

}

