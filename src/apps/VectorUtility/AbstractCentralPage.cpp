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
    WEXPECTNE(nullptr, mpStack);
    TSTALLOC(mpColumnSet);
    TSTALLOC(mpGridLayout);
    TSTALLOC(mpPageTitleLabel);
    connect(mpColumnSet, SIGNAL(columnChanged(VectorColumn::Role)),
            this, SLOT(columnChanged(VectorColumn::Role)));
    connect(mpColumnSet, SIGNAL(columnChanged(VectorColumn)),
            this, SLOT(columnChanged(VectorColumn)));
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

void AbstractCentralPage::setPageTitle(const QString & title)
{
    TRACEQFI << title;
    WEXPECTNE(nullptr, mpPageTitleLabel);
    if (mpPageTitleLabel) mpPageTitleLabel->setText(title);
    update(); show();
}

void AbstractCentralPage::columnChanged(VectorColumn vc)
{
    TRACEQFI << vc.roleString();
}

void AbstractCentralPage::columnChanged(VectorColumn::Role vcr)
{
    TRACEQFI << VectorColumn::roleString(vcr);
}

void AbstractCentralPage::setNames(void)
{
    TRACEFN()
    mBaseName = pageName();
    // TODO if (flags sequential) ...
    mFullName = mBaseName;
    TRACE << "BaseName" << mBaseName << "FullName" << mFullName;
}
/*
void AbstractCentralPage::scopeChanged(Vector::FileScope scope)
{
    WEXPECTNE(nullptr, mpScopeTitleLabel);
    if (mpScopeTitleLabel)
        mpScopeTitleLabel->setText(Vector::scopeString(scope));
}
*/
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
    VectorColumn vc(VectorColumn::Role(vector->scope()),
                    vector->coefVector());
    setColumn(vc);
}

void AbstractCentralPage::setColumn(VectorColumn column)
{
    TRACEQFI << column.roleString();
    mpColumnSet->set(column);
}
