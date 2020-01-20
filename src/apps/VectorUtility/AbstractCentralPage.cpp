#include "AbstractCentralPage.h"

#include <QGridLayout>

#include "Debug.h"
#include "PageGridLayout.h"


AbstractCentralPage::AbstractCentralPage(CentralStack * parent,
                                         const int flags)
    : QWidget(parent)
    , mpStack(parent)
    , mFlags(flags)
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
    EXPECT(connect(mpColumnSet, SIGNAL(columnChangedRole(VectorColumn::Role)),
            this, SLOT(columnChanged(VectorColumn::Role))));
    EXPECT(connect(mpColumnSet, SIGNAL(columnChanged(VectorColumn)),
            this, SLOT(columnChanged(VectorColumn))));
    mpPageTitleLabel->setText("{PageName}");
    mpGridLayout->setObjectName("QGridLayout:AbstractCentralPage");
    mpGridLayout->addWidget(mpPageTitleLabel, 0, 0, Qt::AlignRight);
    setLayout(mpGridLayout);
    show();
}

QGridLayout * AbstractCentralPage::layout()
{
    return CHKPTR(mpGridLayout);
}

VectorColumn AbstractCentralPage::column(
        const VectorColumnRole::Column col) const
{
    TRACEQFI << VectorColumnRole::columnName(col);
    VCHKPTR(mpColumnSet);
    VectorColumn vc = mpColumnSet->value(col);
    TRACEQFI << vc.columnName() << vc.values().first();
    return vc;
}

void AbstractCentralPage::setPageTitle(const QString & title)
{
    TRACEQFI << title;
    WEXPECTNE(nullptr, mpPageTitleLabel);
    if (mpPageTitleLabel) mpPageTitleLabel->setText(title);
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

void AbstractCentralPage::setNames(void)
{
    TRACEFN()
    mBaseName = pageName();
    // TODO if (flags sequential) ...
    mFullName = mBaseName;
    TRACE << "BaseName" << mBaseName << "FullName" << mFullName;
}

QString AbstractCentralPage::baseName(void) const
{
    return mBaseName;
}

QString AbstractCentralPage::fullName(void) const
{
    return mFullName;
}

QString AbstractCentralPage::suffix(void) const
{
    return mSuffix;
}

int AbstractCentralPage::sequence(void) const
{
    return mSequence;
}

void AbstractCentralPage::setVector(VectorObject * vector)
{
    TRACEQFI << vector->scopeString();
    VectorColumn vc(VectorColumnRole::Column(vector->scope()),
                    vector->coefVector());
    TRACEQFI << "exit";
}

void AbstractCentralPage::setColumn(VectorColumn column)
{
    TRACEQFI << column.columnName();
    mpColumnSet->set(column);
    TRACEQFI << "exit";
}
