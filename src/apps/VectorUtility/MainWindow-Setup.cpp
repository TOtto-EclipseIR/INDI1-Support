// file:: MainWindow-Setup.cpp

#include "MainWindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QTimer>

#include "Debug.h"
#include "Vector.h"

void MainWindow::setupMenuActions(void)
{
    TRACEFN()
    mpFileMenu = menuBar()->addMenu("&File");
    mpFileMenu->setObjectName("QMenu:File");
    menuAction(mpFileMenu, "Open &Baseline", "OpenBaseline");
    menuAction(mpFileMenu, "Open Subject&One", "OpenSubjectOne");
    menuAction(mpFileMenu, "Open Subject&Two", "OpenSubjectTwo");
    menuAction(mpFileMenu, "&Close All", "CloseAll");
    mpFileMenu->addSeparator();
    QAction * quitAction = menuAction(mpFileMenu, "&Quit", "Quit");
    quitAction->setShortcut(QKeySequence::Quit);

    mpViewMenu = menuBar()->addMenu("&View");
    mpViewMenu->setObjectName("QMenu:View");
    QAction * homeAction = menuAction(mpViewMenu, "Home",
               "ViewHome", Vector::nullView, mpViewGroup);
    homeAction->setShortcut(QKeySequence::Cancel); // Esc
    menuAction(mpViewMenu, "Summary",
               "ViewSummary", Vector::Summary, mpViewGroup);
    menuAction(mpViewMenu, "Gri&d",
               "ViewGrid", Vector::Grid, mpViewGroup);
    menuAction(mpViewMenu, "Gra&ph",
               "ViewGraph", Vector::Graph, mpViewGroup);
    menuAction(mpViewMenu, "E&ye Location",
               "ViewEyeLocation", Vector::EyeLocation, mpViewGroup);
    menuAction(mpViewMenu, "&Normal-Reconstruction",
               "ViewNormalRecon", Vector::NormalRecon, mpViewGroup);
    menuAction(mpViewMenu, "Raw &XML",
               "ViewRawXml", Vector::RawXml, mpViewGroup);

    mpWindowMenu = menuBar()->addMenu("&Window");
    mpWindowMenu->setObjectName("QMenu:Window");
    menuAction(mpWindowMenu, "&Baseline",
               "ScopeBaseline", Vector::BaseLine, mpWindowGroup);
    menuAction(mpWindowMenu, "Subject&One",
               "ScopeSubjectOne", Vector::SubjectOne, mpWindowGroup);
    menuAction(mpWindowMenu, "Subject&Two",
               "ScopeSubjectTwo", Vector::SubjectTwo, mpWindowGroup);
    menuAction(mpWindowMenu, "BaseBot&h",
               "ScopeBaseBoth", Vector::BaseBoth, mpWindowGroup);

    QTimer::singleShot(100, this,
                       &MainWindow::setupActionConnections);
}

void MainWindow::setupActionConnections(void)
{
    TRACEFN()
    connect(action("OpenBaseline"), &QAction::triggered,
            this, &MainWindow::openBaseline);
    connect(action("OpenSubjectOne"), &QAction::triggered,
            this, &MainWindow::openSubjectOne);
    connect(action("OpenSubjectTwo"), &QAction::triggered,
            this, &MainWindow::openSubjectTwo);
    connect(action("CloseAll"), &QAction::triggered,
            this, &MainWindow::closeAll);
    connect(qApp, &QApplication::aboutToQuit,
            this, &MainWindow::closeAll);
    connect(action("Quit"), &QAction::triggered,
            qApp, &QApplication::quit);
    connect(mpWindowGroup, &QActionGroup::triggered,
            this, &MainWindow::windowGroupTriggered);
    connect(mpViewGroup, &QActionGroup::triggered,
            this, &MainWindow::viewGroupTriggered);
    emit setupComplete();
}

QAction *  MainWindow::menuAction(QMenu * menu,
                            const QString & menuText,
                            const QString & actionName,
                            const QVariant & actionData,
                            QActionGroup * actionGroup)
{
//    TRACE << Q_FUNC_INFO << menu->title() << menuText
  //        << actionName << actionData;
    QAction * newAction = menu->addAction(menuText);
    if ( ! actionData.isNull()) newAction->setData(actionData);
    newAction->setObjectName("QAction:"+actionName);
    if (actionGroup)
    {
        newAction->setCheckable(true);
        actionGroup->addAction(newAction);
    }
    mNameActionMap.insert(actionName, newAction);
    return newAction;
}


QList<QAction *> MainWindow::menuActions(QMenu *menu) const
{
    TRACEFN()
    QList<QAction *> result;
    foreach (QAction * action, mNameActionMap.values())
        if (action->menu() == menu) result.append(action);
    return  result;
}
