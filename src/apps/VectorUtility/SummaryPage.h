#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"

class SummaryView;

class SummaryPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit SummaryPage(CentralStack * parent);
    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:
    void setVector(VectorObject * vector) override;

protected slots:
    void startSetup(void);
    void finishSetup(void)
    { emit setupFinished(); }


signals:
    void ctorFinished(void);
    void setupFinished(void);

private:
    QVector<SummaryView *> mViewVector;
};
