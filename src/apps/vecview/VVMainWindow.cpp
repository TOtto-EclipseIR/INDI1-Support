#include "VVMainWindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QTimer>

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

void VVMainWindow::setupActions(void)
{

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


    QMenuBar * appMenuBar = menuBar();
    QMenu * fileMenu = appMenuBar->addMenu("&File");
    QMenu * helpMenu = appMenuBar->addMenu("Help");
#if 0
    foreach (Key key, allKeys())
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

