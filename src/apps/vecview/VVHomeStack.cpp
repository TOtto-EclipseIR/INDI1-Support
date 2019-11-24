#include "VVHomeStack.h"

#include <QTimer>

#include "base/Debug.h"

#include "VVMainWindow.h"
#include "VVHomeCoverPage.h"
#include "VVIndexPage.h"

VVHomeStack::VVHomeStack(VVMainWindow * parent)
    : QTabWidget(parent)
    , cmpMainWindow(parent)
    , mpHomePage(new VVHomeCoverPage(this))
    , mpIndexPage(new VVIndexPage(this))
{
    TRACEFN()
    setObjectName("VVHomeStack");
    QTimer::singleShot(100, this, SLOT(setupPages()));
}

void VVHomeStack::setupPages()
{
    TRACEFN()
    setTabPosition(QTabWidget::West);
//    QWidget * widget1 = new VVHomeCoverPage(this);
  //  QWidget * widget2 = new VVIndexPage(this);
    addTab(mpHomePage, "Home");
    addTab(mpIndexPage, "Index");
    TRACE << "emit pagesSetup() Home & Index";
    emit pagesSetup();
}
