#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"


class BlankPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit BlankPage(AbstractCentralPage * parent);

public slots:




signals:

protected slots:
    void setup0(void);

private:

};

