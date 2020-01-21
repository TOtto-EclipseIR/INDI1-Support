#include "GridPage.h"

#include <QTimer>

#include "Debug.h"

GridPage::GridPage(CentralStack * parent)
    : AbstractCentralPage(parent)
    , mpTableWidget(new VectorColumnTableWidget
                    (parent->master()->rows(), this))
{
    TRACEFN()
    TSTALLOC(mpTableWidget);
    setObjectName("GridPage");

    mpTableWidget->setRows(stack()->master()->rows());
    mpTableWidget->configure(stack()->master()->
                             settings("VectorColumnTableWidget"));
    mpTableWidget->fillTable();

    connect(this, &GridPage::ctorFinished,
            this, &GridPage::startSetup);
    emit ctorFinished();
}

Vector::View GridPage::view() const
{
    return Vector::Grid;
}

QString GridPage::pageName() const
{
    return QString("Grid");
}

void GridPage::setVector(VectorObject * vector)
{
    VCHKPTR(vector);
    AbstractCentralPage::setVector(vector);
    VCHKPTR(mpTableWidget);
    Vector::FileScope scope = vector->scope();
    TRACEQFI << scope;
    mpTableWidget->setUnitVector(scope, vector->coefVector());
}

void GridPage::startSetup(void)
{
    TRACEFN()

    QTimer::singleShot(100, this, &GridPage::setupViews);
}

void GridPage::setupViews(void)
{
    TRACEFN()
    layout()->addWidget(mpTableWidget, 1, 0, 5, 5);
//    mpTableWidget->fillHeaders();
    update(); show();
    finishSetup();
    TRACEQFI << "exit";
}
