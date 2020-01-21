#include "CentralStack.h"

#include <QTimer>

#include "AbstractCentralPage.h"
#include "Debug.h"
#include "MainWindow.h"

#include "GraphPage.h"
#include "GridPage.h"
#include "HomePage.h"
#include "RawXmlPage.h"
#include "ReconPage.h"
#include "SummaryPage.h"

CentralStack::CentralStack(MainWindow * parent)
    : QStackedWidget(parent)
    , mpMaster(parent->master())
{
    TRACEFN()
    setObjectName("CentralStack:VectorUtility");

    //EXPECT(connect(this, ))
    EXPECT(connect(this, &QStackedWidget::currentChanged,
            this, &CentralStack::indexChanged));

    emit ctorFinished();
}

AbstractCentralPage * CentralStack::page(const Vector::View view)
{
    TRACEQFI << Vector::viewString(view);
    AbstractCentralPage * pacp = mViewPageDMap.at(view);
    VCHKPTR(pacp)
    TRACEQFI << "return" << pacp->objectName();
    return pacp;
}

AbstractCentralPage * CentralStack::widget(int ix) const
{
    TRACEQFI << ix;
    QWidget * pw = QStackedWidget::widget(ix);
    VCHKPTR(pw)
    AbstractCentralPage * pacp
            = qobject_cast<AbstractCentralPage *>(pw);
    VCHKPTR(pacp)
    TRACEQFI << "return" << pacp->objectName();
    return pacp;
}

void CentralStack::setCurrentView(const Vector::View & view)
{
    TRACEQFI << view << Vector::viewString(view);
    if (0 == view)
    {
        TODO("undo workaround");
        setCurrentWidget(mpHomePage);
    }
    else
    {
        AbstractCentralPage * page = nullptr;
        int n = QStackedWidget::count();
        WEXPECTNE(0, QStackedWidget::count())
        if (n)
        {
            for (int ix = 0; ix < n; ix++)
            {
                page = widget(ix);
                VCHKPTR(page);
                TRACE << "trying" << page->objectName() << page->view() << Vector::viewString(page->view());
                if (page->view() == view)
                {
                    QStackedWidget::setCurrentIndex(ix);
                    TRACEQFI << "success" << page->objectName() << page->pageName();
                    break;
                }
                WEXPECTNE(n, ix);
            }
        }
    }
    update(); show();
    TRACEQFI << "exit";
}
/*
void CentralStack::setCurrentPage(const QString & pageName)
{
    TRACEQFI << pageName << "of" << mViewPageDMap.keys();
    QWidget * newPage = mViewPageDMap.at(pageName);
    VCHKPTR(newPage);
    setCurrentWidget(newPage);
    TRACE << newPage->objectName();
    updateGeometry();
    update();
    show();
    TRACEQFI << "exit";
}
*/

void CentralStack::startSetup(void)
{
    TRACEFN()

    EXPECT(connect(master()->mainWindow(), &MainWindow::viewChanged,
            this, &CentralStack::setCurrentView));
    NEEDDO("fill view queue");
    QTimer::singleShot(100, this, &CentralStack::setupNextPage);
    TRACEQFI << "exit";
}

void CentralStack::setupNextPage(void)
{
    TRACEFN()

    if (mPendingSetupQueue.isEmpty())
    {
        TRACE << "Pending Page Setup Queue is empty";
        setCurrentView(Vector::Home);
        setupFinished();
    }
    else
    {
        Vector::View newView = mPendingSetupQueue.takeFirst();
        TRACE <<  "New View Page:" << Vector::viewString(newView);
        switch (newView)
        {
        case Vector::Home:
        {
            mpHomePage = new HomePage(this);
            TSTALLOC(mpHomePage);
            addCentralPage(mpHomePage);
        }
            break;

        case Vector::Summary:
        {
            SummaryPage * summaryPage = new SummaryPage(this);
            TSTALLOC(summaryPage);
            addCentralPage(summaryPage);
        }
            break;

        case Vector::Grid:
        {
            GridPage * gridPage = new GridPage(this);
            TSTALLOC(gridPage);
            addCentralPage(gridPage);
        }
            break;

        case Vector::Graph:
        {
            GraphPage * graphPage = new GraphPage(this);
            TSTALLOC(graphPage);
            addCentralPage(graphPage);
        }
            break;

        case Vector::Reconstruction:
        {
            ReconPage * reconPage = new ReconPage(this);
            TSTALLOC(reconPage);
            addCentralPage(reconPage);
        }
            break;

        case Vector::RawXml:
        {
            RawXmlPage * rawXmlPage = new RawXmlPage(this);
            TSTALLOC(rawXmlPage);
            addCentralPage(rawXmlPage);
        }
            break;

        default:
            WARN << "View Page not handled";
            break;
        }
        emit pageSetupStart(newView);
    }
    TRACEQFI << "exit";
}

void CentralStack::setVector(VectorObject * vector)
{
    TRACEQFI << vector->scopeString();
    VCHKPTR(vector);
    TRACEQFI << Vector::scopeString(vector->scope());
    QList<Vector::View> pageViews = mViewPageDMap.keys();
    TRACE << pageViews;
    foreach(Vector::View view, pageViews)
    {
        AbstractCentralPage * page
            = (AbstractCentralPage *)mViewPageDMap.at(view);
        VCHKPTR(page);
        page->setVector(vector);
    }
/*
    TRACE << "VectorColumn setVC(VectorColumnRole::Column(vector->scope()), vector->coefVector())";
    VectorColumn setVC(VectorColumnRole::Column(vector->scope()),
                       vector->coefVector());
*/
    TRACEQFI << "exit";
}

void CentralStack::addCentralPage(AbstractCentralPage * newPage)
{
    VCHKPTR(newPage);
    TRACEQFI << newPage->objectName() << newPage->pageName();
    newPage->setPageTitle();
    QStackedWidget::addWidget(newPage);
    mViewPageDMap.insertUnique(newPage->view(), newPage);
    show();
    TRACEQFI << "exit";
}

void CentralStack::indexChanged(int newIndex)
{
    TRACEQFI << newIndex;
    AbstractCentralPage * newPage = widget(newIndex);
    VCHKPTR(newPage);
    TRACE << newPage->objectName() << newPage->pageName();
    emit currentPageChanged(newPage->pageName(), newPage);
    TRACEQFI << "exit";
}
