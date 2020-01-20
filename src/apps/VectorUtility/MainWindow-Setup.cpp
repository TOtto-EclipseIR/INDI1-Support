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

void MainWindow::startSetup(QObject *thisObject)
{
    Q_UNUSED(thisObject);
    QTimer::singleShot(100, this, &MainWindow::setupMenuActions);

}

void MainWindow::setupMenuActions(void)
{
    TRACEFN()
    mpFileMenu = menuBar()->addMenu("&File");
    mpFileMenu->setObjectName("QMenu:File");
    menuAction(mpFileMenu, "Open &Baseline", "OpenBaseline");
    menuAction(mpFileMenu, "Open Subject&One", "OpenSubjectOne");
    menuAction(mpFileMenu, "Open Subject&Two", "OpenSubjectTwo");
    menuAction(mpFileMenu, "Close &All", "CloseAll");
    mpFileMenu->addSeparator();
    QAction * quitAction = menuAction(mpFileMenu, "&Quit", "Quit");
    quitAction->setShortcut(QKeySequence::Quit);

    mpViewMenu = menuBar()->addMenu("&View");
    mpViewMenu->setObjectName("QMenu:View");
    QAction * homeAction = menuAction(mpViewMenu, "Home",
               "ViewHome", Vector::nullView, mpViewActionGroup);
    homeAction->setShortcut(QKeySequence::Cancel); // Esc
    menuAction(mpViewMenu, "&Summary",
               "ViewSummary", Vector::Summary, mpViewActionGroup);
    menuAction(mpViewMenu, "Gri&d",
               "ViewGrid", Vector::Grid, mpViewActionGroup);
    menuAction(mpViewMenu, "Gra&ph",
               "ViewGraph", Vector::Graph, mpViewActionGroup);
    menuAction(mpViewMenu, "&Reconstruction",
               "ViewNormalRecon", Vector::Reconstruction, mpViewActionGroup);
    menuAction(mpViewMenu, "Raw &XML",
               "ViewRawXml", Vector::RawXml, mpViewActionGroup);
    QTimer::singleShot(100, this,
                       &MainWindow::setupStatus);
    TRACEQFI << "exit";
}


void MainWindow::setupStatus(void)
{
    TRACEFN()
    QStatusBar * statusBar = QMainWindow::statusBar();
    connect(statusBar, &QStatusBar::messageChanged,
            this, &MainWindow::messageChanged);
    QTimer::singleShot(100, this,
                       &MainWindow::setupActionConnections);
    TRACEQFI << "exit";
}

void MainWindow::setupActionConnections(void)
{
    TRACEFN()
    EXPECT(connect(action("OpenBaseline"), &QAction::triggered,
            this, &MainWindow::openBaseline));
    EXPECT(connect(action("OpenSubjectOne"), &QAction::triggered,
            this, &MainWindow::openSubjectOne));
    EXPECT(connect(action("OpenSubjectTwo"), &QAction::triggered,
            this, &MainWindow::openSubjectTwo));
    EXPECT(connect(action("CloseAll"), &QAction::triggered,
            this, &MainWindow::closeAll));
    EXPECT(connect(qApp, &QApplication::aboutToQuit,
            this, &MainWindow::closeAll));
    EXPECT(connect(action("Quit"), &QAction::triggered,
            qApp, &QApplication::quit));
    show();
    emit setupFinished(this);
    TRACEQFI << "exit";
}

QAction *  MainWindow::menuAction(QMenu * menu,
                            const QString & menuText,
                            const QString & actionName,
                            const QVariant & actionData,
                            QActionGroup * actionGroup)
{
    VCHKPTR(menu);
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


QList<QAction *> MainWindow::menuActions(QMenu * menu) const
{
    TRACEFN()
    QList<QAction *> result;
    foreach (QAction * action, mNameActionMap.values())
    {
        VCHKPTR(action);
        if (action->menu() == menu)
            result.append(action);
    }
    TRACEQFI << "return" << result;
    return  result;
}
