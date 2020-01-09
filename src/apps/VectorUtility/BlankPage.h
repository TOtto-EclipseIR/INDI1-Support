#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"


class BlankPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit BlankPage(CentralStack * parent,
                       const int flags=0);
    virtual QString pageName(void) const override;

public slots:

protected slots:
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }


signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

private:

};

