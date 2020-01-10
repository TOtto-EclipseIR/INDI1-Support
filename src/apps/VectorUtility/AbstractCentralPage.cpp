#include "AbstractCentralPage.h"

#include <QGridLayout>

AbstractCentralPage::AbstractCentralPage(CentralStack * parent, const int flags)
    : QWidget(parent)
    , mpStack(parent)
    , mFlags(flags)
    , mpGridLayout(new QGridLayout)
    , mpPageTitleLabel(new QLabel)
{
    setObjectName("AbstractCentralPage");
    mpPageTitleLabel->setText("PageName");
    mpGridLayout->addWidget(mpPageTitleLabel);
    setLayout(mpGridLayout);
    show();
}

QGridLayout *AbstractCentralPage::layout()
{
    return mpGridLayout;
}

void AbstractCentralPage::setPageTitle(const QString & title)
{
    mpPageTitleLabel->setText(title);
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

void AbstractCentralPage::setNames()
{
    mBaseName = pageName();
    // TODO if (flags sequential) ...
    mFullName = mBaseName;
}
