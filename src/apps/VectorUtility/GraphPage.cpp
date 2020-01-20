#include "GraphPage.h"


#include <QTimer>
#include <QVariantMap>

#include "Debug.h"
#include "VectorUtilityApp.h"


GraphPage::GraphPage(CentralStack * parent,
                     const int flags)
    : AbstractCentralPage(parent, flags)
    , mpVectorPixmapLabel(new QLabel)
    , mpDeltaPixmapLabel(new QLabel)
    , mpRatioPixmapLabel(new QLabel)
{
    TRACEFN()
    setObjectName("GraphPage");
    TSTALLOC(mpVectorPixmapLabel);
    TSTALLOC(mpDeltaPixmapLabel);
    TSTALLOC(mpRatioPixmapLabel);
    mpVectorPixmapLabel->setObjectName("GraphPage:VectorPixmapLabel");
    mpDeltaPixmapLabel->setObjectName("GraphPage:DeltaPixmapLabel");
    mpRatioPixmapLabel->setObjectName("GraphPage:RatioPixmapLabel");
    setNames();
    connect(this, &GraphPage::ctorFinished,
            this, &GraphPage::startSetup);
    emit ctorFinished(this);
}

Vector::View GraphPage::view() const
{
    return Vector::Graph;
}

QString GraphPage::pageName(void) const
{
    return QString("Graph");
}

void GraphPage::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    QVariantMap settings = stack()->
            master()->settings("UnitVectorGraph");
    mUnitVectorGraph.configure(settings);
    QPixmap formPixmap = mUnitVectorGraph.formPixmap();
    mpVectorPixmapLabel->setPixmap(formPixmap);
    layout()->addWidget(mpVectorPixmapLabel, 1, 0, 1, 5);
    layout()->addWidget(mpDeltaPixmapLabel, 2, 0, 1, 5);
    layout()->addWidget(mpRatioPixmapLabel, 3, 0, 1, 5);
    show();
    TRACEQFI << "exit";
    finishSetup(this);
}

void GraphPage::columnChanged(const VectorColumnRole::Column col)
{
    UNUSED(col);
    TRACEQFI << VectorColumn::columnName(col);
    updateUnitPixmap();
}

void GraphPage::updateUnitPixmap(void)
{
    TRACEFN()
    mpVectorPixmapLabel->setPixmap(mUnitVectorGraph
                             .graphPixmap(columnSet()));
    mpVectorPixmapLabel->update();
    mpVectorPixmapLabel->show();
    mpDeltaPixmapLabel->setPixmap(mUnitDeltaGraph
                             .graphPixmap(columnSet()));
    mpDeltaPixmapLabel->update();
    mpDeltaPixmapLabel->show();
    mpRatioPixmapLabel->setPixmap(mUnitRatioGraph
                             .graphPixmap(columnSet()));
    mpRatioPixmapLabel->update();
    mpRatioPixmapLabel->show();
    update(); show();
}
