#include "ActionInfo.h"

#include <QtDebug>
#include <QKeySequence>

ActionInfo::ActionInfo(const VariableId & name)
{
    if ( ! name.isNull()) set("Name", name);
}

QAction * ActionInfo::newAction(QObject * actionParent)
{
    QAction * action = new QAction(value("Text").toString(),
                                   actionParent);
    mpAction = action;
    action->setToolTip(value("ToolTip").toString());
    action->setStatusTip(value("StatusTip").toString());
    action->setShortcut(QKeySequence(value("Shortcut").toString()));
    return action;
}

QString ActionInfo::title() const
{
    return value("Name").toString().isNull()
            ? value("Text").toString()
            : value("Name").toString();

}

void ActionInfo::debug() const
{
    qDebug() << value("Name") << value("Text")
             << value("Shortcut") << value("ToolTip")
             << value("StatusTip");
    if (action())
        qDebug() << action()->objectName();
}

