#include "CentralStack.h"

#include <QTimer>

#include "AbstractCentralPage.h"
#include "Debug.h"
#include "MainWindow.h"

#include "GraphPage.h"
#include "GridPage.h"
#include "HomePage.h"
#include "RawXmlPage.h"
#include "SummaryPage.h"

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
    TRACE << Q_FUNC_INFO << view << Vector::viewString(view);
    if (0 == view)
    {
        TODO("undo workaround");
        setCurrentWidget(mpHomePage);
    }
    else
    {
#if 1
        AbstractCentralPage * page;
        int n = QStackedWidget::count();
        for (int x = 0; x < n; x++)
        {
            page = (AbstractCentralPage *)(QStackedWidget::widget(x));
            TRACE << "trying" << page->objectName() << page->view() << Vector::viewString(page->view());
            if (page->view() == view)
            {
                QStackedWidget::setCurrentIndex(x);
                TRACEQFI << "success" << page->objectName() << page->fullName();
                break;
            }
        }
        WARNQFI << "failed";
#else
        int x = 0;
        while ((page = (AbstractCentralPage *)(widget(x++))))
            if (view == page->view())
                setCurrentWidget(page);
#endif
    }
    show();
}

void CentralStack::setCurrentPage(const QString & fullName)
{
    TRACEQFI << fullName << "of" << mFullNamePageDMap.keys();
    QWidget * newPage = mFullNamePageDMap.at(fullName);
    VCHKPTR(newPage);
    setCurrentWidget(newPage);
    TRACE << newPage->objectName();
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

void CentralStack::setupPages(void)
{
    TRACEFN()
    mpHomePage = new HomePage(this, 0);
    TSTALLOC(mpHomePage);
    addCentralPage(mpHomePage);

    SummaryPage * summaryPage = new SummaryPage(this, 0);
    TSTALLOC(summaryPage);
    addCentralPage(summaryPage);

    GraphPage * graphPage = new GraphPage(this, 0);
    TSTALLOC(graphPage);
    addCentralPage(graphPage);

    GridPage * gridPage = new GridPage(this, 0);
    TSTALLOC(gridPage);
    gridPage->setIndex(0, master()->rows());
    addCentralPage(gridPage);

    addCentralPage(new RawXmlPage(this));

    QTimer::singleShot(100, this, &CentralStack::setupConnections);
}

void CentralStack::setupConnections(void)
{
    TRACEFN()
    connect(master()->mainWindow(), &MainWindow::viewChanged,
            this, &CentralStack::setCurrentView);
    setCurrentPage("Home");
    setupFinished(this);
}

void CentralStack::setVector(VectorObject * vector)
{
    VCHKPTR(vector);
    TRACEQFI << Vector::scopeString(vector->scope());
    QStringList pageNames = mFullNamePageDMap.keys();
    TRACE << pageNames;
    foreach(QString pageName, pageNames)
    {
        AbstractCentralPage * page
            = (AbstractCentralPage *)mFullNamePageDMap.at(pageName);
        VCHKPTR(page);
        page->setVector(vector);
    }

}

void CentralStack::scopeChanged(Vector::FileScope scope)
{
    TRACEQFI << Vector::scopeString(scope);
    mCurrentScope = scope;
    QStringList pageNames = mFullNamePageDMap.keys();
    TRACE << pageNames;
    foreach(QString pageName, pageNames)
    {
        AbstractCentralPage * page
            = (AbstractCentralPage *)mFullNamePageDMap.at(pageName);
        VCHKPTR(page);
        page->scopeChanged(scope);
    }
}

void CentralStack::addCentralPage(AbstractCentralPage * newPage)
{
    VCHKPTR(newPage);
    TRACEQFI << newPage->objectName() << newPage->fullName();
    newPage->setPageTitle(newPage->pageName());
    QStackedWidget::addWidget(newPage);
    mFullNamePageDMap.insertUnique(newPage->fullName(), newPage);
    connect(this, &CentralStack::currentScopeChanged,
            newPage, &AbstractCentralPage::scopeChanged);
    show();
}

void CentralStack::indexChanged(int newIndex)
{
    QWidget * newPage = QStackedWidget::widget(newIndex);
    VCHKPTR(newPage);
    TRACEQFI << Q_FUNC_INFO << newPage->objectName()
          << qobject_cast<AbstractCentralPage *>(newPage)->fullName();
    emit currentPageChanged(mFullNamePageDMap.at(newPage), newPage);
}
