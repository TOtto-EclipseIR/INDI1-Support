#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"

class SummaryView;

class SummaryPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit SummaryPage(CentralStack * parent,
                         const int flags=0);
    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:
    void setVector(VectorObject * vector) override;

protected slots:
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }


signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

private:
    QVector<SummaryView *> mViewVector;
};
