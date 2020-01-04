#include "AbstractCentralPage.h"

#include <QGridLayout>

AbstractCentralPage::AbstractCentralPage(CentralStack * parent, const int flags)
    : QWidget(parent)
    , mpStack(parent)
    , mFlags(flags)
    , mpGridLayout(new QGridLayout)
{
    setObjectName("AbstractCentralPage");
    setLayout(mpGridLayout);
    show();
}

QGridLayout *AbstractCentralPage::layout()
{
    return mpGridLayout;
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
