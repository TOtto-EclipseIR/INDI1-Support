#include "GridPage.h"

#include <QGridLayout>
#include <QTimer>

#include "Debug.h"

GridPage::GridPage(CentralStack * parent,
                     const int flags)
    : AbstractCentralPage(parent, flags)
    , mpTableView(new VectorTableView(this))
{
    TRACEFN()
    setObjectName("GridPage");

    QTimer::singleShot(100, this, &GridPage::setupViews);
}

QString GridPage::pageName() const
{
    return QString("Grid");
}

void GridPage::setModel(VectorTableModel *model)
{
    mpTableModel = model;
    setupModel();
}

void GridPage::setupModel()
{
    mpTableView->setModel(mpTableModel);
}

void GridPage::setupViews()
{
    TRACEFN()
    layout()->addWidget(mpTableView);

    //    QTimer::singleShot(100, this, &GridPage::setup1);
}
