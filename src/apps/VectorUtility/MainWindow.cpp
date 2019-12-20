#include "MainWindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QTimer>

#include "Debug.h"
#include "Vector.h"
#include "VectorItemDelegate.h"
#include "VectorTableHorizontalHeader.h"
#include "VectorTableView.h"
#include "VectorTableVerticalHeader.h"


MainWindow::MainWindow(VectorUtilityApp * parent)
    : mpMaster(parent)
    , mpTableView(new VectorTableView(this))
    , mpVerticalHeader(new VectorTableVerticalHeader(this))
    , mpHorizontalHeader(new VectorTableHorizontalHeader(this))
    , mpItemDelegate(new VectorItemDelegate(this))
    , mpViewGroup(new QActionGroup(this))
    , mpWindowGroup(new QActionGroup(this))
{
    TRACEFN()
    setObjectName("MainWindow:VectorUtility");
    mpViewGroup->setObjectName("QActionGroup:View");
    mpViewGroup->setExclusive(true);
    mpWindowGroup->setObjectName("QActionGroup:Window");
    mpWindowGroup->setExclusive(true);
    QTimer::singleShot(100, this, &MainWindow::setupMenuActions);
}

MainWindow::~MainWindow()
{
}

void MainWindow::openBaseline(void)
{
    TRACEFN()
    openVectorDialog(Vector::BaseLineFile);
}

void MainWindow::openSubjectOne(void)
{
    TRACEFN()
    openVectorDialog(Vector::SubjectOneFile);
}

void MainWindow::openSubjectTwo(void)
{
    TRACEFN()
    openVectorDialog(Vector::SubjectTwoFile);
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
    close(Vector::BaseLineFile);
    close(Vector::SubjectOneFile);
    close(Vector::SubjectTwoFile);
}

void MainWindow::close(const Vector::FileScope scope)
{
    TRACE << Q_FUNC_INFO << Vector::scopeString(scope);
    emit closeScope(scope);
}

void MainWindow::windowGroupTriggered(QAction * action)
{
    TRACE << Q_FUNC_INFO << action->objectName() << action->data();
    emit windowChanged(Vector::Window(action->data().toInt()));

}

void MainWindow::viewGroupTriggered(QAction * action)
{
    TRACE << Q_FUNC_INFO << action->objectName() << action->data();
    emit viewChanged(Vector::View(action->data().toInt()));

}

QAction * MainWindow::action(const QString &actionName) const
{
    TRACEFN()
    return mNameActionMap.value(actionName);
}


