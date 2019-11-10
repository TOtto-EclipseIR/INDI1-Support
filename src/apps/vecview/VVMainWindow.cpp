#include "VVMainWindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QTimer>

#include "core/VariableIdList.h"
#include "exe/Settings.h"

VVMainWindow::VVMainWindow(void)
    : cmpSettings(new Settings())
{
    setObjectName("VVMainWindow");
    QTimer::singleShot(100, this, SLOT(setupActions()));
}

VVMainWindow::~VVMainWindow()
{
}

void VVMainWindow::configure()
{
    Variable::List vbls;
    vbls << Variable("Actions/Quit/Name", "Quit")
         << Variable("Actions/Quit/Text", "&Quit")
         << Variable("Actions/Quit/Menu", "File")
         ;
     mConfiguration.set(vbls);
}

void VVMainWindow::setupActions(void)
{
#if 0
    Settings::KeyValueList fileActions;
    Settings::KeyValueList helpActions;
    fileActions
            << Settings::KeyValuePair("OpenVectorFiles/Text",
                                      "&Open Vector Files")
            << Settings::KeyValuePair("Quit/Text", "&Quit")
               ;
    helpActions
            << Settings::KeyValuePair("AboutQt/Text",
                                      "About&Qt")
               ;
    cmpSettings->set("Actions/File", fileActions);
    cmpSettings->set("Actions/Help", helpActions);
#endif

    QMenuBar * appMenuBar = menuBar();
    QMap<QString, QMenu *> nameMenuMap;
    QMenu * fileMenu = appMenuBar->addMenu("&File");
    nameMenuMap.insert("File", fileMenu);
    QMenu * helpMenu = appMenuBar->addMenu("Help");
    nameMenuMap.insert("Help", helpMenu);
#if 1
    foreach (VariableId vid, mConfiguration.exportSection("Actions").ids())
    {

    }
#else
    QAction * actQuit = new QAction("&Quit");
    connect(actQuit, SIGNAL(triggered()),
            qApp, SLOT(quit()));
    fileMenu->addAction(actQuit);
#endif
    appMenuBar->show();
}

