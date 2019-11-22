#include "VectorSetWidget.h"

#include <QLabel>
#include <QTabWidget>
#include <QTextEdit>
#include <QTimer>

#include "../../libs/base/Debug.h"

#include "VectorSetGraphics.h"

VectorSetWidget::VectorSetWidget(VectorSetDocument * doc)
    : cmpDocument(doc)
    , cmpMainTabWidget(new QTabWidget(this))
    , cmpRawXmlPage(new QTextEdit((QWidget *)(cmpMainTabWidget)))
    , cmpGraphicsPage(new VectorSetGraphics((QWidget *)(cmpMainTabWidget)))
    , mpLabel(new QLabel())
{
    TRACEFN()
    setObjectName("VectorSetWidget");
    QTimer::singleShot(100, this, SLOT(setupWidget()));
}

void VectorSetWidget::setupWidget(void)
{
    TRACEFN()

}
