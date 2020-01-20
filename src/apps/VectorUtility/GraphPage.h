#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"

#include "UnitDeltaGraph.h"
#include "UnitRatioGraph.h"
#include "UnitVectorGraph.h"

class GraphPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit GraphPage(CentralStack * parent,
                       const int flags=0);

    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:

protected slots:
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }
    void columnChanged(VectorColumnRole::Column col) override;
    void updateUnitPixmap(void);

signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

private:
    QLabel * mpVectorPixmapLabel=nullptr;
    QLabel * mpDeltaPixmapLabel=nullptr;
    QLabel * mpRatioPixmapLabel=nullptr;
    UnitVectorGraph mUnitVectorGraph;
    UnitDeltaGraph mUnitDeltaGraph;
    UnitRatioGraph mUnitRatioGraph;
};

