#include "RawXmlPage.h"

#include <QTextEdit>
#include <QTimer>

#include "Debug.h"
#include "MainWindow.h"
#include "Vector.h"
#include "VectorObject.h"
#include "VectorUtilityApp.h"

RawXmlPage::RawXmlPage(CentralStack * parent,
                     const int flags)
    : AbstractCentralPage(parent, flags)
{
    TRACEFN()
    setObjectName("RawXmlPage");
    setNames();
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

void RawXmlPage::setVector(VectorObject * vector)
{
    if (vector)
    {
        scopeChanged(vector->scope());
        VCHKPTR(mpTextEdit);
        mpTextEdit->setPlainText(vector->data().getXmlString());
        showVector(vector);
    }
}

void RawXmlPage::startSetup(QObject * thisObject)
{
    TRACEFN()
    UNUSED(thisObject);

    mpTextEdit = new QTextEdit(this);
    TSTALLOC(mpTextEdit);
    mpTextEdit->setObjectName("QTextEdit:RawXmlPage");
    mpTextEdit->setFontFamily("Lucida Console");
    mpTextEdit->setFontPointSize(14);
    mpTextEdit->setReadOnly(true);

    layout()->setColumnStretch(2, 2);
    layout()->addWidget(mpTextEdit, 1, 0, 1, 3);
    setLayout(layout());
    update();
    updateGeometry();
    show();

    connect(stack()->master(), &VectorUtilityApp::vectorSet,
            this, &RawXmlPage::setVector);

    finishSetup(this);
}

void RawXmlPage::scopeChanged(Vector::FileScope scope)
{
    TRACEQFI << Vector::scopeString(scope);
    showVector(vector(scope));
}

void RawXmlPage::showVector(VectorObject * newVec)
{
    VCHKPTR(newVec);
    VCHKPTR(mpTextEdit);
    TRACEQFI << (newVec ? Vector::scopeString(newVec->scope()) : "NULL")
            << mpTextEdit->objectName();
    setScopeTitle(newVec->scope());
    mpTextEdit->setPlainText(newVec->data().getXmlString());
}
