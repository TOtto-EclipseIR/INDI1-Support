#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"

#include "Vector.h"
#include "VectorObject.h"

class QTextEdit;

class RawXmlPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit RawXmlPage(CentralStack * parent,
                       const int flags=0);
    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:

protected slots:
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }
//    virtual void scopeChanged(Vector::FileScope scope);
//    void showVector(VectorObject * newVec);
    virtual void setVector(VectorObject * vector) override;


signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

private:
    QTextEdit * mpBaselineText=nullptr;
    QTextEdit * mpSubjectOneText=nullptr;
    QTextEdit * mpSubjectTwoText=nullptr;
};
