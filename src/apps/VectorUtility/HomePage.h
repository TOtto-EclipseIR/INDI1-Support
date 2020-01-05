#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"


class HomePage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit HomePage(CentralStack * parent,
                       const int flags=0);
    virtual QString pageName(void) const override;

public slots:




signals:

protected slots:
    void setupWidgets(void);

private:

};

