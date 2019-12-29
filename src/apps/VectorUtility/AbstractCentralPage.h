#pragma once

#include <QWidget>

#include "CentralStack.h"

class AbstractCentralPage : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractCentralPage(CentralStack * parent);
    CentralStack * stack(void)
    { return mpStack; }

public slots:



signals:


private:
    CentralStack * mpStack;
};

