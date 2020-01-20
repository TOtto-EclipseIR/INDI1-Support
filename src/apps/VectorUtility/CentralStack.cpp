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

    EXPECT(connect(this, &QStackedWidget::currentChanged,
            this, &CentralStack::indexChanged));
    emit ctorFinished(this);
}

AbstractCentralPage * CentralStack::page(const QString &fullName)
{
    TRACEQFI << fullName;
    AbstractCentralPage * pacp = mFullNamePageDMap.at(fullName);
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
                    TRACEQFI << "success" << page->objectName() << page->fullName();
                    break;
                }
                WEXPECTNE(n, ix);
            }
        }
    }
    update(); show();
    TRACEQFI << "exit";
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
    TRACEQFI << "exit";
}


void CentralStack::startSetup(QObject *thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    QTimer::singleShot(100, this, &CentralStack::setupPages);
    TRACEQFI << "exit";
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
    addCentralPage(gridPage);

    ReconPage * reconPage = new ReconPage(this, 0);
    TSTALLOC(reconPage);
    addCentralPage(reconPage);

    RawXmlPage * rawXmlPage = new RawXmlPage(this, 0);
    TSTALLOC(rawXmlPage);
    addCentralPage(rawXmlPage);

    QTimer::singleShot(100, this, &CentralStack::setupConnections);
    TRACEQFI << "exit";
}

void CentralStack::setupConnections(void)
{
    TRACEFN()
    EXPECT(connect(master()->mainWindow(), &MainWindow::viewChanged,
            this, &CentralStack::setCurrentView));
    setCurrentPage("Home");
    setupFinished(this);
    TRACEQFI << "exit";
}

void CentralStack::setVector(VectorObject * vector)
{
    TRACEQFI << vector->scopeString();
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
    TRACEQFI << newPage->objectName() << newPage->fullName();
    newPage->setPageTitle(newPage->pageName());
    QStackedWidget::addWidget(newPage);
    mFullNamePageDMap.insertUnique(newPage->fullName(), newPage);
    show();
    TRACEQFI << "exit";
}

void CentralStack::indexChanged(int newIndex)
{
    TRACEQFI << newIndex;
    AbstractCentralPage * newPage = widget(newIndex);
    VCHKPTR(newPage);
    TRACE << newPage->objectName() << newPage->fullName();
    emit currentPageChanged(mFullNamePageDMap.at(newPage), newPage);
    TRACEQFI << "exit";
}
