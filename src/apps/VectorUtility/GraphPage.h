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
    explicit GraphPage(CentralStack * parent);

    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:

protected slots:
    void startSetup(void);
    void finishSetup(void)
    { emit setupFinished(); }
    void columnChanged(VectorColumnRole::Column col) override;
    void updateUnitPixmap(void);

signals:
    void ctorFinished(void);
    void setupFinished(void);

private:
    QLabel * mpVectorPixmapLabel=nullptr;
    QLabel * mpDeltaPixmapLabel=nullptr;
    QLabel * mpRatioPixmapLabel=nullptr;
    UnitVectorGraph mUnitVectorGraph;
    UnitDeltaGraph mUnitDeltaGraph;
    UnitRatioGraph mUnitRatioGraph;
};

