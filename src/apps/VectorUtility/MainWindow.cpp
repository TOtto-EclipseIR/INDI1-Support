#include "MainWindow.h"

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimer>

#include "CentralStack.h"
#include "Debug.h"
#include "Vector.h"
#include "VectorTableWidget.h"


MainWindow::MainWindow(VectorUtilityApp * parent)
    : mpApp(parent)
    , mpViewActionGroup(new QActionGroup(this))
{
    TRACEFN()
    TSTALLOC(mpApp)
    WANTDO("Try ABORT flush"); // << "This" << "is a" << "test" << "of the" << "ABORT" << "Debug macro")
    TSTALLOC(mpViewActionGroup)
    setObjectName("MainWindow:VectorUtility");
    mpViewActionGroup->setObjectName("QActionGroup:View");
    mpViewActionGroup->setExclusive(true);

    QDir  qrc(":/images/jpg");
    QFileInfoList qrcInfos = qrc.entryInfoList();
    TRACE << qrcInfos;

    EXPECT(connect(mpApp, &VectorUtilityApp::setupFinished,
            this, &MainWindow::startSetup));
    connect(this, &MainWindow::ctorFinished,
            this, &MainWindow::startSetup);
    emit ctorFinished();
}

MainWindow::~MainWindow()
{
}

VectorUtilityApp * MainWindow::app()
{
    return mpApp;
}

CentralStack * MainWindow::stack()
{
    return mpCentralStack;
}

void MainWindow::openBaseline(void)
{
    TRACEFN()
    openVectorDialog(Vector::Baseline);
}

void MainWindow::openSubjectOne(void)
{
    TRACEFN()
    openVectorDialog(Vector::SubjectOne);
}

void MainWindow::openSubjectTwo(void)
{
    TRACEFN()
    openVectorDialog(Vector::SubjectTwo);
}

void MainWindow::openSearchResults(void)
{
    TRACEFN()
    QString dirName = QFileDialog::getExistingDirectory(this,
                                    "Open SearchResult Directory");
    if (dirName.isEmpty()) return;
    QDir searchResultDir(dirName);
    emit searchResults(searchResultDir);
}

void MainWindow::openVectorDialog(Vector::FileScope scope)
{
    TRACE << Q_FUNC_INFO << Vector::scopeString(scope);
    QString fileName = QFileDialog::getOpenFileName(this);
    if (fileName.isEmpty())
        emit openDialogCancelled(scope);
    else
        emit openDialogFileName(scope, fileName);
}

void MainWindow::closeAll(void)
{
    TRACEFN()
    close(Vector::Baseline);
    close(Vector::SubjectOne);
    close(Vector::SubjectTwo);
}

void MainWindow::close(const Vector::FileScope scope)
{
    TRACE << Q_FUNC_INFO << Vector::scopeString(scope);
    emit closeScope(scope);
}

void MainWindow::viewGroupTriggered(QAction * action)
{
    TRACE << Q_FUNC_INFO << action->objectName() << action->data();
    emit viewChanged(Vector::View(action->data().toInt()));

}

void MainWindow::showMessage(const QString & status,
                             const int msecTime)
{
    QMainWindow::statusBar()->showMessage(status, msecTime);
}

void MainWindow::clearMessage()
{
    QMainWindow::statusBar()->clearMessage();
}

void MainWindow::setVector(VectorObject * vector)
{
    TRACEQFI << Vector::scopeString(vector->scope());
    stack()->setVector(vector);
    TODO("Refactor: SIGNAL direect to CentralStack")
}


QAction * MainWindow::action(const QString & actionName) const
{
    TRACEQFI << actionName;
    QAction * act = mNameActionMap.value(actionName);
    TRACEQFI << "return" << act->objectName();
    return act;
}


