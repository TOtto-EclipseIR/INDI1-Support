#include "VVMainWindow.h"

#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>

VVMainWindow::VVMainWindow(void)
{
    setObjectName("VVMainWindow");
    QMenuBar * appMenuBar = menuBar();
    QAction * actQuit = new QAction("&Quit");
    connect(actQuit, SIGNAL(triggered()),
            qApp, SLOT(quit()));
    QMenu * fileMenu = appMenuBar->addMenu("&File");
    fileMenu->addAction(actQuit);
    appMenuBar->show();
}

VVMainWindow::~VVMainWindow()
{
}

