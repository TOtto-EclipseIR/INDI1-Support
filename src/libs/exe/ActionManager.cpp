#include "ActionManager.h"

#include <QtDebug>
#include <QMenu>

#include "../core/VariableIdList.h"

#include "ActionInfo2.h"

ActionManager::ActionManager(QObject * parent)
    : QObject(parent)
{
    setObjectName("ActionManager");
}

void ActionManager::configure(const VariableSet & config)
{
    qDebug() << Q_FUNC_INFO;
    VariableSet actionConfig = config.exportSection("Actions");
    VariableIdList ids = actionConfig.sectionIds();
    qDebug() << ids;
    foreach (VariableId actionName, ids)
    {
        ActionInfo2 ai(actionName);
        VariableSet sectionConfig
                = actionConfig.exportSection(actionName);
        foreach (VariableId id, sectionConfig.ids())
        {
            QVariant var = sectionConfig.value(id);
            qDebug() << id << var;
            ai.set(id, var);
        }
        QAction * action = ai.newAction(this);
        action->setObjectName("QAction:"
                              + ai.value("Name").toString());
        ai.debug();
        mNameActionInfoMap.insert(actionName, ai);
    }
}

