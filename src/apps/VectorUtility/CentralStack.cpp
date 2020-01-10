#include "CentralStack.h"

#include <QTimer>

#include "AbstractCentralPage.h"
#include "Debug.h"
#include "MainWindow.h"

#include "GridPage.h"
#include "HomePage.h"
#include "RawXmlPage.h"

CentralStack::CentralStack(MainWindow * parent)
    : QStackedWidget(parent)
    , mpMaster(parent->master())
{
    TRACEFN()
    setObjectName("CentralStack:VectorUtility");
    connect(this, &QStackedWidget::currentChanged,
            this, &CentralStack::indexChanged);
    emit ctorFinished(this);
}

void CentralStack::setCurrentView(const Vector::View & view)
{
    TRACE << Q_FUNC_INFO << view;
    int x = 0;
    AbstractCentralPage * page;
    while (page = (AbstractCentralPage *)(widget(x++)))
        if (view == page->view())
            setCurrentWidget(page);
}

void CentralStack::setCurrentPage(const QString & fullName)
{
    TRACEQFI << fullName << mFullNamePageDMap.keys();
    QWidget * newPage = mFullNamePageDMap.at(fullName);
    if (newPage)
    {
        setCurrentWidget(newPage);
        TRACE << newPage->objectName();
    }
    updateGeometry();
    update();
    show();
}

void CentralStack::startSetup(QObject *thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    QTimer::singleShot(100, this, &CentralStack::setupPages);

}

void CentralStack::setupPages()
{
    TRACEFN()
    addCentralPage(new HomePage(this, 0));

    GridPage * gridPage = new GridPage(this, 0);
    gridPage->setModel(master()->tableModel());
    addCentralPage(gridPage);

    addCentralPage(new RawXmlPage(this));

    QTimer::singleShot(100, this, &CentralStack::setupConnections);
}

void CentralStack::setupConnections()
{
    TRACEFN()
    connect(master()->mainWindow(), &MainWindow::viewChanged,
            this, &CentralStack::setCurrentView);
    setCurrentPage("Home");
    setupFinished(this);
}

void CentralStack::addCentralPage(AbstractCentralPage * newPage)
{
    TRACEQFI << newPage->objectName();
    // TODO TBD
    newPage->setPageTitle(newPage->pageName());
    QStackedWidget::addWidget(newPage);
    mFullNamePageDMap.insertUnique(newPage->fullName(), newPage);
    // UNDO
    show();
}

void CentralStack::indexChanged(int newIndex)
{
    QWidget * newPage = QStackedWidget::widget(newIndex);
    TRACE << Q_FUNC_INFO << newPage->objectName()
          << qobject_cast<AbstractCentralPage *>(newPage)->fullName();
    emit currentChanged(mFullNamePageDMap.at(newPage), newPage);
}
