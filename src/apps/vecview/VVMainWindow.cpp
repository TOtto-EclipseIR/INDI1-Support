#include "VVMainWindow.h"

#include <QtDebug>
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QSettings>
#include <QTimer>

#include "base/Debug.h"
#include "core/VariableIdList.h"
#include "exe/ActionManager.h"
#include "exe/DocumentActions.h"
#include "exe/DocumentManager.h"
#include "exe/Settings.h"

#include "VVHomeStack.h"
#include "VVHomeCoverPage.h"
#include "VVIndexPage.h"

VVMainWindow::VVMainWindow(void)
    : mpSettings(new Settings())
    , mpMainTabWidget(new QTabWidget(this))
    , mpHomeStack(new VVHomeStack(this))
    , mpActionManager(new ActionManager(this))
    , mpDocumentActions(new DocumentActions(this))
    , mpDocumentManager(new DocumentManager(this))
{
    TRACEFN()
    setObjectName("VVMainWindow");
    mpDocumentActions->setParentWidget(this);
    QTimer::singleShot(100, this, SLOT(configure()));
}

void VVMainWindow::configure(void)
{
    TRACEFN()
    Variable::List vbls;
    vbls << Variable("Actions/Quit/Name", "Quit")
         << Variable("Actions/Quit/Text", "&Quit")
         << Variable("Actions/Quit/Shortcut", "Alt+F4")
         << Variable("Actions/Quit/Menu", "File")
         << Variable("Actions/OpenFiles/Name", "OpenFiles")
         << Variable("Actions/OpenFiles/Text", "&Open File(s)...")
         << Variable("Actions/OpenFiles/Shortcut", "Ctl+O")
         << Variable("Actions/OpenFiles/Menu", "File")
         << Variable("Actions/AboutQt/Name", "AboutQt")
         << Variable("Actions/AboutQt/Text", "About &Qt")
         << Variable("Actions/AboutQt/Menu", "Help")
         << Variable("Document/OpenFiles/Caption",
                     "Open VectorSet File(s)")
         << Variable("Document/OpenFiles/Filter",
                     "XML VectorSet Files (*.XML)"
                     ";;Images with VectorSet (*.PNG)"
                     ";;All files (*.*)")
         ;
     mConfiguration.set(vbls);

     QTimer::singleShot(100, this, SLOT(setupActions()));
}

void VVMainWindow::setupActions(void)
{
    TRACEFN()
    mpActionManager->configure(mConfiguration);
    QTimer::singleShot(100, this, SLOT(setupMenus()));
}

void VVMainWindow::setupMenus()
{
    TRACEFN()
    QMenuBar * appMenuBar = menuBar();

    //----- File Menu -----
    QMenu * fileMenu = appMenuBar->addMenu("&File");
    fileMenu->setObjectName("fileMenu");
    mNameMenuMap.insert("File", fileMenu);
    ActionInfo ai = mpActionManager->actionInfo("OpenFiles");
    fileMenu->addAction(ai.action());
    fileMenu->addSeparator();
    ai = mpActionManager->actionInfo("Quit");
    fileMenu->addAction(ai.action());

    //----- Help Menu -----
    QMenu * helpMenu = appMenuBar->addMenu("Help");
    helpMenu->setObjectName("helpMenu");
    ai = mpActionManager->actionInfo("AboutQt");
    helpMenu->addAction(ai.action());

    appMenuBar->show();
    QTimer::singleShot(100, this, SLOT(setupWindows()));
}


void VVMainWindow::setupWindows()
{
    TRACEFN()
    TRACE << "mpMainTabWidget->addTab(mpHomeStack, Home);";
    mpMainTabWidget->addTab(mpHomeStack, "Home");
    BaseMainWindow::setCentralWidget(mpMainTabWidget);
    show();
    QTimer::singleShot(100, this, SLOT(makeConnections()));
}


void VVMainWindow::makeConnections()
{
    TRACEFN()
    ActionInfo ai;

    ai = mpActionManager->actionInfo("OpenFiles");
    connect(ai.action(), SIGNAL(triggered()),
            mpDocumentActions, SLOT(openFilesDialog()));
    ai = mpActionManager->actionInfo("Quit");
    connect(ai.action(), SIGNAL(triggered()),
            qApp, SLOT(quit()));
    ai = mpActionManager->actionInfo("AboutQt");
    connect(ai.action(), SIGNAL(triggered()),
            qApp, SLOT(aboutQt()));
}

