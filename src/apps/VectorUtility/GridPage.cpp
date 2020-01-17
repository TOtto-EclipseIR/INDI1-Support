#include "GridPage.h"

#include <QTimer>

#include "Debug.h"

GridPage::GridPage(CentralStack * parent,
                     const int flags)
    : AbstractCentralPage(parent, flags)
    , mpTableWidget(new VectorColumnTableWidget(this))
{
    TRACEFN()
    TSTALLOC(mpTableWidget);
    setObjectName("GridPage");
    setNames();
    connect(this, &GridPage::ctorFinished,
            this, &GridPage::startSetup);
    emit ctorFinished(this);
}

Vector::View GridPage::view() const
{
    return Vector::Grid;
}

QString GridPage::pageName() const
{
    return QString("Grid");
}

void GridPage::setIndex(int indexColumn, int rowCount)
{
    TRACEFN()
    mpTableWidget->fillIndex(indexColumn, rowCount);
}

void GridPage::setVector(VectorObject * vector)
{
    VCHKPTR(vector);
    VCHKPTR(mpTableWidget);
    Vector::FileScope scope = vector->scope();
    TRACEQFI << scope;
    mpTableWidget->fillVector(scope, vector->coefVector());
}

void GridPage::startSetup(QObject * thisObject)
{
    TRACEFN()
    UNUSED(thisObject);
    QTimer::singleShot(100, this, &GridPage::setupViews);
}

void GridPage::setupViews(void)
{
    TRACEFN()
    layout()->addWidget(mpTableWidget, 1, 0, 1, 3);
    setLayout(layout());
    updateGeometry();
    update();
    show();
    finishSetup(this);
    TRACEQFI << "exit";
}
