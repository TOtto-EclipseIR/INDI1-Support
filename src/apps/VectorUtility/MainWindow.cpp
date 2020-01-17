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
    : mpMaster(parent)
    , mpCentralStack(new CentralStack(this))
    , mpViewActionGroup(new QActionGroup(this))
//    , mpScopeActionGroup(new QActionGroup(this))
{
    TRACEFN()
    setObjectName("MainWindow:VectorUtility");
    mpMaster->setMainWindow(this);
    mpViewActionGroup->setObjectName("QActionGroup:View");
    mpViewActionGroup->setExclusive(true);
//    mpScopeActionGroup->setObjectName("QActionGroup:Scope");
  //  mpScopeActionGroup->setExclusive(true);
    QMainWindow::setCentralWidget(mpCentralStack);

    QDir  qrc(":/images/jpg");
    QFileInfoList qrcInfos = qrc.entryInfoList();
    TRACE << qrcInfos;

    connect(this, &MainWindow::ctorFinished,
            this, &MainWindow::startSetup);
    connect(this, &MainWindow::setupFinished,
            mpCentralStack, &CentralStack::startSetup);
//    connect(master(), &VectorUtilityApp::setVector,
  //          mpCentralStack, &CentralStack::setVector);
    emit ctorFinished(this);
}

MainWindow::~MainWindow()
{
}

VectorUtilityApp * MainWindow::master()
{
    VCHKPTR(mpMaster);
    return mpMaster;
}

CentralStack * MainWindow::stack(void)
{
    VCHKPTR(mpCentralStack);
    return mpCentralStack;
}

void MainWindow::openBaseline(void)
{
    TRACEFN()
    openVectorDialog(Vector::BaseLine);
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
    close(Vector::BaseLine);
    close(Vector::SubjectOne);
    close(Vector::SubjectTwo);
}

void MainWindow::close(const Vector::FileScope scope)
{
    TRACE << Q_FUNC_INFO << Vector::scopeString(scope);
    emit closeScope(scope);
}
/*
void MainWindow::scopeGroupTriggered(QAction * action)
{
    TRACE << Q_FUNC_INFO << action->objectName() << action->data();
    emit scopeChanged(Vector::FileScope(action->data().toInt()));

}
*/
void MainWindow::viewGroupTriggered(QAction * action)
{
    TRACE << Q_FUNC_INFO << action->objectName() << action->data();
    emit viewChanged(Vector::View(action->data().toInt()));

}
/*
void MainWindow::setScopeCheck(Vector::FileScope scope)
{
    TRACEQFI << Vector::scopeString(scope);
    foreach(QAction * action, menuActions(scopeMenu()))
        if (action->data().toInt() == scope)
            action->setChecked(true);
}
*/
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
    VCHKPTR(vector);
    TRACEQFI << Vector::scopeString(vector->scope());
    stack()->setVector(vector);
}


QAction * MainWindow::action(const QString & actionName) const
{
    TRACEQFI << actionName;
    QAction * act = mNameActionMap.value(actionName);
    VCHKPTR(act);
    TRACE << "return" << act->objectName();
    return act;
}


