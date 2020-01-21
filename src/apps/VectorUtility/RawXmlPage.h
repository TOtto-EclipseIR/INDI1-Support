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
    explicit RawXmlPage(CentralStack * parent);
    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:

protected slots:
    void startSetup(void);
    void finishSetup(void)
    { emit setupFinished(); }
//    virtual void scopeChanged(Vector::FileScope scope);
//    void showVector(VectorObject * newVec);
    virtual void setVector(VectorObject * vector) override;


signals:
    void ctorFinished(void);
    void setupFinished(void);

private:
    QTextEdit * mpBaselineText=nullptr;
    QTextEdit * mpSubjectOneText=nullptr;
    QTextEdit * mpSubjectTwoText=nullptr;
};
