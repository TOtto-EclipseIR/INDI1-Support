#include "BlankPage.h"

#include <QTimer>

#include "Debug.h"

BlankPage::BlankPage(CentralStack * parent,
                     const int flags)
    : AbstractCentralPage(parent, flags)
{
    TRACE <<  "NOT INTENDED TO BE INSTANCIATED; EXAMPLE ONLY";
    Q_ASSERT(false);
    // Remove above two lines to race

    TRACEFN()
    setObjectName("BlankPage");

    connect(this, &BlankPage::ctorFinished,
            this, &BlankPage::startSetup);
    emit ctorFinished(this);
    //    QTimer::singleShot(100, this, &BlankPage::setup0);
}

QString BlankPage::pageName() const
{
    return QString("Blank");
}

void BlankPage::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    finishSetup(this);
}
