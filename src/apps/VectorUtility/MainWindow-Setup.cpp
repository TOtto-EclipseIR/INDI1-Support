// file:: MainWindow-Setup.cpp

#include "MainWindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimer>

#include "Debug.h"
#include "Vector.h"

void MainWindow::startSetup(void)
{
    TRACEFN()
    QTimer::singleShot(100, this, &MainWindow::setupMenuActions);
    TRACEQFI << "exit";
}

void MainWindow::setupMenuActions(void)
{
    TRACEFN()
    mpFileMenu = menuBar()->addMenu("&File");
    mpFileMenu->setObjectName("QMenu:File");
    addMenuAction(mpFileMenu, "Open &Baseline", "OpenBaseline");
    addMenuAction(mpFileMenu, "Open Subject&One", "OpenSubjectOne");
    addMenuAction(mpFileMenu, "Open Subject&Two", "OpenSubjectTwo");
    addMenuAction(mpFileMenu, "Close &All", "CloseAll");
    mpFileMenu->addSeparator();
    addMenuAction(mpFileMenu, "Open Search &Results",
                              "OpenSearchResults");
    mpFileMenu->addSeparator();
    QAction * quitAction = addMenuAction(mpFileMenu, "&Quit", "Quit");
    quitAction->setShortcut(QKeySequence::Quit);

    mpViewMenu = menuBar()->addMenu("&View");
    mpViewMenu->setObjectName("QMenu:View");
    QAction * homeAction = addMenuAction(mpViewMenu, "Home",
               "ViewHome", Vector::nullView, mpViewActionGroup);
    homeAction->setShortcut(QKeySequence::Cancel); // Esc
    addMenuAction(mpViewMenu, "&Summary",
               "ViewSummary", Vector::Summary, mpViewActionGroup);
    addMenuAction(mpViewMenu, "Gri&d",
               "ViewGrid", Vector::Grid, mpViewActionGroup);
    addMenuAction(mpViewMenu, "Gra&ph",
               "ViewGraph", Vector::Graph, mpViewActionGroup);
    addMenuAction(mpViewMenu, "&Reconstruction",
               "ViewNormalRecon", Vector::Reconstruction, mpViewActionGroup);
    addMenuAction(mpViewMenu, "Raw &XML",
               "ViewRawXml", Vector::RawXml, mpViewActionGroup);

    TRACEQFI << "sshot setupActionConnesetupStatusctions() & exit";
    QTimer::singleShot(100, this,
                       &MainWindow::setupStatusBar);
}

void MainWindow::setupStatusBar(void)
{
    TRACEFN()
    LIKEDO("setStatusLabel(), startStatusProgress(), enableCancel()")

    mpStatusBar = QMainWindow::statusBar();
    connect(mpStatusBar, &QStatusBar::messageChanged,
            this, &MainWindow::messageChanged);
    TRACEQFI << "sshot setupActionConnections() & exit";
    LIKEDO("mainToolBar")
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
    connect(action("OpenSearchResults"), &QAction::triggered,
            this, &MainWindow::openSearchResults);
    connect(action("CloseAll"), &QAction::triggered,
            this, &MainWindow::closeAll);
    connect(qApp, &QApplication::aboutToQuit,
            this, &MainWindow::closeAll);
    connect(action("Quit"), &QAction::triggered,
            this, &QApplication::quit);
    show();

    TRACEQFI << "sshot finishSetup() & exit";
    QTimer::singleShot(100, this, &MainWindow::finishSetup);
}

void MainWindow::finishSetup()
{
    TRACEFN()
    mpCentralStack = new CentralStack(this);
    emit setupFinished();
    TRACEQFI << "emit setupFinished(); & exit";
}

QAction *  MainWindow::addMenuAction(QMenu * menu,
                            const QString & menuText,
                            const QString & actionName,
                            const QVariant & actionData,
                            QActionGroup * actionGroup)
{
    TRACEQFI << menu->title() << menuText << actionName << actionData << (actionGroup ? actionGroup->objectName() : "no Group");
    QAction * newAction = menu->addAction(menuText);
    TSTALLOC(newAction);
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


QList<QAction *> MainWindow::actionsFor(QMenu *menu) const
{
    TRACEFN()
    QList<QAction *> result;
    foreach (QAction * action, mNameActionMap.values())
    {
        if (action->menu() == menu)
            result.append(action);
    }
    TRACEQFI << "return" << result;
    return  result;
}
