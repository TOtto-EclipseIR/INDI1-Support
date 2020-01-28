#pragma once

#include <QWidget>

#include <QGridLayout>
#include <QLabel>
#include <QTimer>

#include "CentralStack.h"
#include "PageGridLayout.h"
#include "Vector.h"
#include "VectorColumn.h"
#include "VectorColumnSet.h"
#include "VectorObject.h"
#include "VectorUtilityApp.h"

class AbstractCentralPage : public QWidget
{
    Q_OBJECT
public:
//    friend class CentralStack;

protected:
    explicit AbstractCentralPage(CentralStack * parent);
    CentralStack * stack(void)
    { return mpStack; }
    QGridLayout * layout(void);
    VectorObject * vector(const Vector::FileScope scope)
    { return stack()->app()->vector(scope); }
    VectorColumn column(const VectorColumnRole::Column col) const;
    VectorColumnSet * columnSet(void) const
    { return mpColumnSet; }

public: // virtual
    virtual Vector::View view(void) const = 0;
    virtual QString pageName(void) const = 0;
    virtual QString pageTitle(void) const;

public slots:
    void setPageTitle(void);
    void setColumn(VectorColumn column);

public slots: // virtual
    virtual void startSetup(void);
    virtual void finishSetup(void);
    virtual void setVector(VectorObject * vector);

protected: // virtual

protected slots: // virtual
    virtual void columnChanged(VectorColumn vc);
    virtual void columnChanged(VectorColumnRole::Column col);

signals:
    void ctorFinished(void);
    void setupFinished(Vector::View view);

private:
    CentralStack * mpStack=nullptr;
    VectorColumnSet * mpColumnSet=nullptr;
    PageGridLayout * mpGridLayout=nullptr;
    QLabel * mpPageTitleLabel=nullptr;
};

