#include "VectorSetWidget.h"


#include <QTabWidget>
#include <QTextEdit>
#include "VectorSetGraphics.h"

VectorSetWidget::VectorSetWidget(VectorSetDocument * doc)
    : cmpDocument(doc)
    , cmpMainTabWidget(new QTabWidget(this))
    , cmpRawXmlPage(new QTextEdit((QWidget *)(cmpMainTabWidget)))
    , cmpGraphicsPage(new VectorSetGraphics((QWidget *)(cmpMainTabWidget)))
{
    setObjectName("VectorSetWidget");
}

void VectorSetWidget::setupWidget(void)
{

}
