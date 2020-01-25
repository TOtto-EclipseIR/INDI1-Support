#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"


class HomePage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit HomePage(CentralStack * parent);
    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:

protected slots:
    void startSetup(void);
    void finishSetup(void)
    { emit setupFinished(); }



signals:
    void ctorFinished(void);
    void setupFinished(void);

protected slots:
    void setupWidgets(void);

private:

};

