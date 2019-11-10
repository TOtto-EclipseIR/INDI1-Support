#include "VVMainWindow.h"

#include <QtDebug>
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QTimer>

#include "core/VariableIdList.h"
#include "exe/ActionManager.h"
#include "exe/Settings.h"

VVMainWindow::VVMainWindow(void)
    : cmpSettings(new Settings())
    , cmpActionManager(new ActionManager(this))
{
    setObjectName("VVMainWindow");
    QTimer::singleShot(100, this, SLOT(configure()));
}

VVMainWindow::~VVMainWindow()
{
}

void VVMainWindow::configure(void)
{
    qDebug() << Q_FUNC_INFO;
    Variable::List vbls;
    vbls << Variable("Actions/Quit/Name", "Quit")
         << Variable("Actions/Quit/Text", "&Quit")
         << Variable("Actions/Quit/Shortcut", "Alt+F4")
         << Variable("Actions/Quit/Menu", "File")
         << Variable("Actions/Open/Name", "Open")
         << Variable("Actions/Open/Text", "&Open File(s)...")
         << Variable("Actions/Open/Shortcut", "Ctl+O")
         << Variable("Actions/Open/Menu", "File")
         ;
     mConfiguration.set(vbls);
     QTimer::singleShot(100, this, SLOT(setupMenus()));
}

void VVMainWindow::setupMenus()
{
    qDebug() << Q_FUNC_INFO;
    QMenuBar * appMenuBar = menuBar();
    QMenu * fileMenu = appMenuBar->addMenu("&File");
    fileMenu->setObjectName("fileMenu");
    mNameMenuMap.insert("File", fileMenu);
    QMenu * helpMenu = appMenuBar->addMenu("Help");
    helpMenu->setObjectName("helpMenu");
    mNameMenuMap.insert("Help", helpMenu);
    appMenuBar->show();
    QTimer::singleShot(100, this, SLOT(setupActions()));
}

void VVMainWindow::setupActions(void)
{
    qDebug() << Q_FUNC_INFO;
    cmpActionManager->configure(mConfiguration);
    QTimer::singleShot(100, this, SLOT(fillMenus()));

}

void VVMainWindow::fillMenus()
{
    qDebug() << Q_FUNC_INFO;
    QMenu * menu = mNameMenuMap.value("File");
    if (menu)
    {
        ActionInfo2 ai = cmpActionManager->actionInfo("Open");
        ai.debug();
        if (ai.action())
            menu->addAction(ai.action());
        menu->addSeparator();
        ai = cmpActionManager->actionInfo("Quit");
        ai.debug();
        if (ai.action())
            menu->addAction(ai.action());
    }
}

