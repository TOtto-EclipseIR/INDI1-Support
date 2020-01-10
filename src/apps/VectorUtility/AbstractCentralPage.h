#pragma once

#include <QWidget>

#include <QGridLayout>
#include <QLabel>

#include "CentralStack.h"
#include "Vector.h"

class AbstractCentralPage : public QWidget
{
    Q_OBJECT
public:

protected:
    explicit AbstractCentralPage(CentralStack * parent,
                                 const int flags=0);
    QGridLayout * layout(void);

public:
    CentralStack * stack(void)
    { return mpStack; }
    void setPageTitle(const QString & title);

public: // virtual
    virtual Vector::View view(void) const = 0;
    virtual QString pageName(void) const = 0;
    virtual QString baseName(void) const;
    virtual QString fullName(void) const;
    virtual QString suffix(void) const;
    virtual int sequence(void) const;

public slots:

protected: // virtual
    virtual void setNames(void);


signals:


private:
    CentralStack * mpStack;
    int mFlags=0;
    QString mBaseName;
    QString mFullName;
    QString mSuffix;
    int mSequence=0;
    QGridLayout * mpGridLayout=nullptr;
    QLabel * mpPageTitleLabel=nullptr;
};

