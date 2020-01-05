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
#include "VectorItemDelegate.h"
#include "VectorTableHorizontalHeader.h"
#include "VectorTableView.h"
#include "VectorTableVerticalHeader.h"
#include "VectorTableWidget.h"


MainWindow::MainWindow(VectorUtilityApp * parent)
    : mpMaster(parent)
    , mpCentralStack(new CentralStack(this))
    , mpTablePageWidget(new VectorTableWidget(mpCentralStack))
    , mpViewActionGroup(new QActionGroup(this))
    , mpScopeActionGroup(new QActionGroup(this))
{
    TRACEFN()
    setObjectName("MainWindow:VectorUtility");
    mpMaster->set(this);
    mpViewActionGroup->setObjectName("QActionGroup:View");
    mpViewActionGroup->setExclusive(true);
    mpScopeActionGroup->setObjectName("QActionGroup:Window");
    mpScopeActionGroup->setExclusive(true);
    QMainWindow::setCentralWidget(mpCentralStack);

    QDir  qrc(":/images/jpg");
    QFileInfoList qrcInfos = qrc.entryInfoList();
    TRACE << qrcInfos;


    QTimer::singleShot(100, this, &MainWindow::setupMenuActions);
    // See MainWondow-Setup.cpp
}

MainWindow::~MainWindow()
{
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

void MainWindow::scopeGroupTriggered(QAction * action)
{
    TRACE << Q_FUNC_INFO << action->objectName() << action->data();
    emit scopeChanged(Vector::FileScope(action->data().toInt()));

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

QAction * MainWindow::action(const QString &actionName) const
{
    TRACEFN()
    return mNameActionMap.value(actionName);
}


