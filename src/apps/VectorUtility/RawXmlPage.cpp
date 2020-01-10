#include "RawXmlPage.h"

#include <QTextEdit>
#include <QTimer>

#include "Debug.h"
#include "VectorObject.h"
#include "VectorTableModel.h"
#include "VectorUtilityApp.h"

RawXmlPage::RawXmlPage(CentralStack * parent,
                     const int flags)
    : AbstractCentralPage(parent, flags)
{
    TRACEFN()
    setObjectName("RawXmlPage");

    connect(this, &RawXmlPage::ctorFinished,
            this, &RawXmlPage::startSetup);
    emit ctorFinished(this);
}

Vector::View RawXmlPage::view() const
{
    return Vector::RawXml;
}

QString RawXmlPage::pageName() const
{
    return QString("RawXML");
}

void RawXmlPage::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);

    mpTextEdit = new QTextEdit(this);
    mpTextEdit->setReadOnly(true);
//    VectorObject * vo = stack()->master()->tableModel()->vector(Vector::BaseLine);
  //  if (vo) mpTextEdit->setPlainText(vo->data().getXmlString());

    layout()->addWidget(mpTextEdit, 1, 0);
    setLayout(layout());
    update();
    updateGeometry();
    show();

    finishSetup(this);
}
