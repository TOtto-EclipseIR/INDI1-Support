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

VVMainWindow::VVMainWindow(void)
    : mpSettings(new Settings())
    , mpMainTabWidget(new QTabWidget(this))
    , mpHomeStack(new VVHomeStack(this))
    , mpHomePage(new VVHomeCoverPage(mpHomeStack))
    , mpActionManager(new ActionManager(this))
    , mpDocumentActions(new DocumentActions(this))
    , mpDocumentManager(new DocumentManager(this))
{
    TRACEFN()
    setObjectName("VVMainWindow");
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
         << Variable("Actions/Open/Name", "Open")
         << Variable("Actions/Open/Text", "&Open File(s)...")
         << Variable("Actions/Open/Shortcut", "Ctl+O")
         << Variable("Actions/Open/Menu", "File")
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

    QMenu * menu = mNameMenuMap.value("File");
    ActionInfo ai = mpActionManager->actionInfo("Open");
    menu->addAction(ai.action());
    menu->addSeparator();

    ai = mpActionManager->actionInfo("Quit");
    menu->addAction(ai.action());

    //----- File Menu -----
    QMenu * helpMenu = appMenuBar->addMenu("Help");
    helpMenu->setObjectName("helpMenu");
    mNameMenuMap.insert("Help", helpMenu);

    appMenuBar->show();

    QTimer::singleShot(100, this, SLOT(setupWindows()));
}


void VVMainWindow::setupWindows()
{
    TRACEFN()

    mpMainTabWidget->addTab(mpHomeStack, "Home");
    BaseMainWindow::setCentralWidget(mpMainTabWidget);
    show();


    QTimer::singleShot(100, this, SLOT(makeConnections()));
}


void VVMainWindow::makeConnections()
{
    TRACEFN()
    ActionInfo ai = mpActionManager->actionInfo("Open");
    connect(ai.action(), SIGNAL(triggered()),
            mpDocumentActions, SLOT(openFilesDialog()));
    ai = mpActionManager->actionInfo("Quit");
    connect(ai.action(), SIGNAL(triggered()),
            qApp, SLOT(quit()));
    connect(mpActionManager, SIGNAL(openFilesList(QFileInfoList)),
            mpDocumentManager, SLOT(openAllFiles(QFileInfoList)));
}

