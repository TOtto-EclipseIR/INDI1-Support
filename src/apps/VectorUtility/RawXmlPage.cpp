#include "RawXmlPage.h"

#include <QTextEdit>
#include <QTimer>

#include "Debug.h"
#include "MainWindow.h"
#include "Vector.h"
#include "VectorObject.h"
#include "VectorUtilityApp.h"

RawXmlPage::RawXmlPage(CentralStack * parent)
    : AbstractCentralPage(parent)
{
    TRACEFN()
    setObjectName("RawXmlPage");
    connect(this, &RawXmlPage::ctorFinished,
            this, &RawXmlPage::startSetup);
    emit ctorFinished();
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
    WEXPECTNE(nullptr, vector)
    if (vector)
    {
        Vector::FileScope scope = vector->scope();
//        scopeChanged(scope);
        switch (scope)
        {
        case Vector::Baseline:
            mpBaselineText->setPlainText(vector->data().getXmlString());
            mpBaselineText->textCursor().movePosition(QTextCursor::Start);
            break;

        case Vector::SubjectOne:
            mpSubjectOneText->setPlainText(vector->data().getXmlString());
            mpSubjectOneText->textCursor().movePosition(QTextCursor::Start);
            break;

        case Vector::SubjectTwo:
            mpSubjectTwoText->setPlainText(vector->data().getXmlString());
            mpSubjectTwoText->textCursor().movePosition(QTextCursor::Start);
            break;

        default:
            WARN << "Invalid case" << scope;
            break;
        }
        update();
        show();
    }
}

void RawXmlPage::startSetup(void)
{
    TRACEFN()


    mpBaselineText = new QTextEdit(this);
    TSTALLOC(mpBaselineText);
    mpBaselineText->setObjectName("QTextEdit:RawXmlPage");
    mpBaselineText->setFontFamily("Lucida Console");
    mpBaselineText->setFontPointSize(14);
    mpBaselineText->setReadOnly(true);

    mpSubjectOneText = new QTextEdit(this);
    TSTALLOC(mpSubjectOneText);
    mpSubjectOneText->setObjectName("QTextEdit:RawXmlPage");
    mpSubjectOneText->setFontFamily("Lucida Console");
    mpSubjectOneText->setFontPointSize(14);
    mpSubjectOneText->setReadOnly(true);

    mpSubjectTwoText = new QTextEdit(this);
    TSTALLOC(mpSubjectTwoText);
    mpSubjectTwoText->setObjectName("QTextEdit:RawXmlPage");
    mpSubjectTwoText->setFontFamily("Lucida Console");
    mpSubjectTwoText->setFontPointSize(14);
    mpSubjectTwoText->setReadOnly(true);


    //layout()->setColumnStretch(2, 2);
    layout()->addWidget(mpBaselineText, 1, 0, 1, 3);
    layout()->addWidget(mpSubjectOneText, 2, 0, 1, 3);
    layout()->addWidget(mpSubjectTwoText, 3, 0, 1, 3);
    setLayout(layout());
//    update();
  //  updateGeometry();
    show();

    connect(stack()->app(), &VectorUtilityApp::vectorSet,
            this, &RawXmlPage::setVector);

    finishSetup();
}
/*
void RawXmlPage::scopeChanged(Vector::FileScope scope)
{
    TRACEQFI << Vector::scopeString(scope);
    showVector(vector(scope));
}
*/
/*
void RawXmlPage::showVector(VectorObject * newVec)
{
    VCHKPTR(newVec);
    VCHKPTR(mpTextEdit);
    TRACEQFI << (newVec ? Vector::scopeString(newVec->scope()) : "NULL")
            << mpTextEdit->objectName();
    mpTextEdit->setPlainText(newVec->data().getXmlString());
}
*/
