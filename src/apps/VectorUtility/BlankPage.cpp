#include "BlankPage.h"

#include <QTimer>

#include "Debug.h"

BlankPage::BlankPage(AbstractCentralPage * parent)
    : AbstractCentralPage(parent->stack())
{
    TRACE <<  "NOT INTENDED TO BE INSTANCIATED; EXAMPLE ONLY";
    Q_ASSERT(false);
    // Remove above two lines to race

    TRACEFN()
    setObjectName("BlankPage");

    QTimer::singleShot(100, this, &BlankPage::setup0);
}

void BlankPage::setup0()
{
    TRACEFN()

    //    QTimer::singleShot(100, this, &BlankPage::setup1);
}
