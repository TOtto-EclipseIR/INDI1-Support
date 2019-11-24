#include "ActionManager.h"

//#include <QtDebug>
#include <QMenu>

#include "../base/Debug.h"
#include "../core/VariableIdList.h"

#include "ActionInfo.h"

ActionManager::ActionManager(QObject * parent)
    : QObject(parent)
{
    TRACEFN()
    setObjectName("ActionManager");
}

void ActionManager::configure(const VariableSet & config)
{
    TRACEFN()
    VariableSet actionConfig = config.exportSection("Actions");
    VariableIdList ids = actionConfig.sectionIds();
    TRACE << ids;
    foreach (VariableId actionName, ids)
    {
        ActionInfo ai(actionName);
        VariableSet sectionConfig
                = actionConfig.exportSection(actionName);
        foreach (VariableId id, sectionConfig.ids())
        {
            QVariant var = sectionConfig.value(id);
            ai.set(id, var);
        }
        QAction * action = ai.newAction(this);
        action->setObjectName("QAction:"
                              + ai.value("Name").toString());
//        ai.debug();
        mNameActionInfoMap.insert(actionName, ai);
    }
}

