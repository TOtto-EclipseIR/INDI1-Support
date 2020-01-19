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
    connect(this, &QStackedWidget::currentChanged,
            this, &CentralStack::indexChanged);
    emit ctorFinished(this);
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
        AbstractCentralPage * page;
        int n = QStackedWidget::count();
        WEXPECTNE(0, QStackedWidget::count())
        if (n)
        {
            for (int ix = 0; ix < n; ix++)
            {
                page = (AbstractCentralPage *)
                            (QStackedWidget::widget(ix));
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
    addCentralPage(gridPage);

    ReconPage * reconPage = new ReconPage(this, 0);
    TSTALLOC(reconPage);
    addCentralPage(reconPage);

    RawXmlPage * rawXmlPage = new RawXmlPage(this, 0);
    TSTALLOC(rawXmlPage);
    addCentralPage(rawXmlPage);

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
    VectorColumn setVC(vector->scope(), vector->coefVector());

}

void CentralStack::addCentralPage(AbstractCentralPage * newPage)
{
    VCHKPTR(newPage);
    TRACEQFI << newPage->objectName() << newPage->fullName();
    newPage->setPageTitle(newPage->pageName());
    QStackedWidget::addWidget(newPage);
    mFullNamePageDMap.insertUnique(newPage->fullName(), newPage);
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
