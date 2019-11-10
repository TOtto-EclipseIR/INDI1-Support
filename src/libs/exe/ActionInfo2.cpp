#include "ActionInfo2.h"

#include <QtDebug>
#include <QKeySequence>

ActionInfo2::ActionInfo2(const VariableId & name)
{
    if ( ! name.isNull()) set("Name", name);
}

QAction * ActionInfo2::newAction(QObject * actionParent)
{
    QAction * action = new QAction(value("Text").toString(),
                                   actionParent);
    mpAction = action;
    action->setToolTip(value("ToolTip").toString());
    action->setStatusTip(value("StatusTip").toString());
    action->setShortcut(QKeySequence(value("Shortcut").toString()));
    return action;
}

void ActionInfo2::debug() const
{
    qDebug() << value("Name") << value("Text")
             << value("Shortcut") << value("ToolTip")
             << value("StatusTip");
    if (action())
        qDebug() << action()->objectName();
}
