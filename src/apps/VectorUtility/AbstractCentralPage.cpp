#include "AbstractCentralPage.h"

AbstractCentralPage::AbstractCentralPage(CentralStack * parent, const int flags)
    : QWidget(parent)
    , mpStack(parent)
    , mFlags(flags)
{
    setObjectName("AbstractCentralPage");
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
