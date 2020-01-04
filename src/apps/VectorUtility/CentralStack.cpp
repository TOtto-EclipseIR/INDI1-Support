#include "CentralStack.h"

#include <QTimer>

#include "AbstractCentralPage.h"
#include "Debug.h"
#include "MainWindow.h"

#include "GridPage.h"
#include "HomePage.h"

CentralStack::CentralStack(MainWindow * parent)
    : QStackedWidget(parent)
    , mpMaster(parent->master())
{
    TRACEFN()
    setObjectName("CentralStack:VectorUtility");
    connect(this, &QStackedWidget::currentChanged,
            this, &CentralStack::indexChanged);


    QTimer::singleShot(100, this, &CentralStack::setupPages);
}

void CentralStack::setCurrentPage(const QString & fullName)
{
    TRACEFN()
    QWidget * newPage = mFullNamePageDMap.at(fullName);
    if (newPage) setCurrentWidget(newPage);
    updateGeometry();
    update();
    show();
}

void CentralStack::setupPages()
{
    TRACEFN()
    addCentralPage(new HomePage(this, 0));

    GridPage * gridPage = new GridPage(this, 0);
    gridPage->setModel(master()->tableModel());
    addCentralPage(gridPage);

    QTimer::singleShot(100, this, &CentralStack::setupComplete);
}

void CentralStack::setupComplete()
{
    TRACEFN()
    setCurrentPage("Home");
}

void CentralStack::addCentralPage(AbstractCentralPage * newPage)
{
    TRACEFN()
    // TODO TBD
    QStackedWidget::addWidget(newPage);
    // UNDO
    show();
//    QStackedWidget::setCurrentWidget(newPage);
}

void CentralStack::indexChanged(int newIndex)
{
    QWidget * newPage = QStackedWidget::widget(newIndex);
    TRACE << Q_FUNC_INFO << newPage->objectName()
          << qobject_cast<AbstractCentralPage *>(newPage)->fullName();
    emit currentChanged(mFullNamePageDMap.at(newPage), newPage);
}
