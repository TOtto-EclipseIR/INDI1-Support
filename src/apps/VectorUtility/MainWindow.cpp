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
{
    TRACEFN()
    TSTALLOC(mpMaster)
    TSTALLOC(mpCentralStack)
    TSTALLOC(mpViewActionGroup)
    setObjectName("MainWindow:VectorUtility");
    mpMaster->setMainWindow(this);
    mpViewActionGroup->setObjectName("QActionGroup:View");
    mpViewActionGroup->setExclusive(true);
    QMainWindow::setCentralWidget(mpCentralStack);

    QDir  qrc(":/images/jpg");
    QFileInfoList qrcInfos = qrc.entryInfoList();
    TRACE << qrcInfos;

    EXPECT(connect(parent, &VectorUtilityApp::setupFinished,
            this, &MainWindow::startSetup));
    EXPECT(connect(this, &MainWindow::setupFinished,
            mpCentralStack, &CentralStack::startSetup));
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
    VCHKPTR(vector);
    TRACEQFI << Vector::scopeString(vector->scope());
    stack()->setVector(vector);
}


QAction * MainWindow::action(const QString & actionName) const
{
    TRACEQFI << actionName;
    QAction * act = mNameActionMap.value(actionName);
    VCHKPTR(act);
    TRACEQFI << "return" << act->objectName();
    return act;
}


