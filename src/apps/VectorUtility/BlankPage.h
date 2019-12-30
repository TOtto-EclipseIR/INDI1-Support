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




signals:

protected slots:
    void setup0(void);

private:

};

