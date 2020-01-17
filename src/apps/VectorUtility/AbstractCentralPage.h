#pragma once

#include <QWidget>

#include <QGridLayout>
#include <QLabel>
#include <QTimer>

#include "CentralStack.h"
#include "Vector.h"
#include "VectorColumn.h"
#include "VectorColumnSet.h"
#include "VectorObject.h"
#include "VectorUtilityApp.h"

class AbstractCentralPage : public QWidget
{
    Q_OBJECT
public:
    friend class CentralStack;

protected:
    explicit AbstractCentralPage(CentralStack * parent,
                                 const int flags=0);
    QGridLayout * layout(void);
    VectorObject * vector(const Vector::FileScope scope)
    { return stack()->master()->vector(scope); }
    VectorColumn column(const int scopeRole) const
    { return mpColumnSet->column(scopeRole); }
    VectorColumnSet * columnSet(void) const
    { return mpColumnSet; }

public:
    CentralStack * stack(void)
    { return mpStack; }
    void setPageTitle(const QString & title);
//    void setScopeTitle(const Vector::FileScope scope);

protected slots: // virtual
    virtual void columnChanged(VectorColumn vc);
    virtual void columnChanged(VectorColumn::Role vcr);

public: // virtual
    virtual Vector::View view(void) const = 0;
    virtual QString pageName(void) const = 0;
    virtual QString baseName(void) const;
    virtual QString fullName(void) const;
    virtual QString suffix(void) const;
    virtual int sequence(void) const;

protected: // virtual
    virtual void setVector(VectorObject * vector);
    virtual void setColumn(VectorColumn column);
//    virtual void scopeChanged(Vector::FileScope scope);
    virtual void setNames(void);

signals:


private:
    CentralStack * mpStack;
    int mFlags=0;
    VectorColumnSet * mpColumnSet=nullptr;
    QString mBaseName;
    QString mFullName;
    QString mSuffix;
    int mSequence=0;
    QGridLayout * mpGridLayout=nullptr;
    QLabel * mpPageTitleLabel=nullptr;
//    QLabel * mpScopeTitleLabel=nullptr;
};

