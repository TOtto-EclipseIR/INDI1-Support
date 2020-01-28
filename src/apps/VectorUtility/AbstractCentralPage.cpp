#include "AbstractCentralPage.h"

#include <QGridLayout>

#include "Debug.h"
#include "PageGridLayout.h"


AbstractCentralPage::AbstractCentralPage(CentralStack * parent)
    : QWidget(parent)
    , mpStack(parent)
    , mpColumnSet(new VectorColumnSet(this))
    , mpGridLayout(new PageGridLayout)
    , mpPageTitleLabel(new QLabel)
{
    TRACEFN()
    setObjectName("AbstractCentralPage");
    TSTALLOC(mpStack);
    TSTALLOC(mpColumnSet);
    TSTALLOC(mpGridLayout);
    TSTALLOC(mpPageTitleLabel);
    CONNECT(mpColumnSet, SIGNAL(columnChangedRole(VectorColumn::Role)),
            this, SLOT(columnChanged(VectorColumn::Role)));
    CONNECT(mpColumnSet, SIGNAL(columnChanged(VectorColumn)),
            this, SLOT(columnChanged(VectorColumn)));
    CONNECT(this, &AbstractCentralPage::setupFinished,
            stack(), &CentralStack::viewSetupFinished);
    mpPageTitleLabel->setText("{PageName}");
    mpGridLayout->setObjectName("QGridLayout:AbstractCentralPage");
    mpGridLayout->addWidget(mpPageTitleLabel, 0, 0, Qt::AlignRight);
    setLayout(mpGridLayout);
    show();
}

QGridLayout * AbstractCentralPage::layout()
{
    return (mpGridLayout);
}

VectorColumn AbstractCentralPage::column(
        const VectorColumnRole::Column col) const
{
    TRACEQFI << VectorColumnRole::columnName(col);
    VectorColumn vc = mpColumnSet->value(col);
    TRACEQFI << vc.columnName() << vc.values().first();
    return vc;
}

QString AbstractCentralPage::pageTitle() const
{
    return pageName();
}

void AbstractCentralPage::setPageTitle(void)
{
    TRACEFN()
    WEXPECTNE(nullptr, mpPageTitleLabel);
    if (mpPageTitleLabel) mpPageTitleLabel->setText(pageTitle());
    update(); show();
    TRACEQFI << "exit";
}

void AbstractCentralPage::columnChanged(VectorColumn vc)
{
    TRACEQFI << vc.columnName() << "exit";
}

void AbstractCentralPage::columnChanged(VectorColumnRole::Column col)
{
    TRACEQFI << VectorColumn::columnName(col) << "exit";
}

void AbstractCentralPage::setVector(VectorObject * vector)
{
    TSTALLOC(vector)
    TRACEQFI << vector->scopeString();
    VectorColumn vc(VectorColumnRole::Column(vector->scope()),
                    vector->coefVector());
    TRACEQFI << "exit";
}

void AbstractCentralPage::setColumn(VectorColumn column)
{
    TRACEQFI << column.columnName();
    TSTALLOC(mpColumnSet)
    mpColumnSet->set(column);
    TRACEQFI << "exit";
}

void AbstractCentralPage::startSetup()
{
    TRACEQFI << Vector::viewString(view());
    TSTALLOC(mpGridLayout)
    setLayout(mpGridLayout);
}

void AbstractCentralPage::finishSetup()
{
    TRACEQFI << Vector::viewString(view());
    emit setupFinished(view());
}
