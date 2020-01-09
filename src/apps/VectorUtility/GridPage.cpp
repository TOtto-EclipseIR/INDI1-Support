#include "GridPage.h"

#include <QGridLayout>
#include <QTimer>

#include "Debug.h"

GridPage::GridPage(CentralStack * parent,
                     const int flags)
    : AbstractCentralPage(parent, flags)
    , mpTableView(new VectorTableView(this))
    , mpHeaderView(new QHeaderView(Qt::Horizontal, this))
{
    TRACEFN()
    setObjectName("GridPage");
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

void GridPage::setModel(VectorTableModel * model)
{
    mpTableModel = model;
    TRACEQFI ;
}

void GridPage::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    QTimer::singleShot(100, this, &GridPage::setupViews);
}

void GridPage::setupViews(void)
{
    TRACEQFI ;
    mpTableView->setModel(mpTableModel);
    mpHeaderView->setModel(mpTableModel);
    layout()->addWidget(mpTableView);
    finishSetup(this);
    TRACEQFI << "return";
}
