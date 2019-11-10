#include "ActionInfo2.h"

#include <QKeySequence>

ActionInfo2::ActionInfo2(const VariableId & name)
{
    if ( ! name.isNull()) set("Name", name);
}

QAction * ActionInfo2::newAction(QObject * actionParent)
{
    QAction * action = new QAction(value("Text").toString(),
                                   actionParent);
    // set("Action", (void *)(action));
    action->setToolTip(value("ToolTip").toString());
    action->setStatusTip(value("StatusTip").toString());
    action->setShortcut(QKeySequence(value("Shortcut").toString()));
    return action;
}
