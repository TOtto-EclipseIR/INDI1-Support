#include "UnitRatioGraph.h"

#include <QPoint>
#include <QRect>
#include <QSize>

#include "Debug.h"
#include "UnitFloat.h"

UnitRatioGraph::UnitRatioGraph(void)
{
    TRACEFN()
}

void UnitRatioGraph::configure(const QVariantMap & settings)
{
    mParms.replace(settings);
}

void UnitRatioGraph::clearFormCache()
{
    mFormPixmapCache = QPixmap();
    WEXPECT(mFormPixmapCache.isNull());
}

void UnitRatioGraph::clearGraphCache()
{
    mGraphPixmapCache = QPixmap();
    WEXPECT(mGraphPixmapCache.isNull());
}

QPixmap UnitRatioGraph::formPixmap(void)
{
    TRACEFN()
#if 1
    WANTDO("implement cache clears")
#else
    if ( ! mFormPixmapCache.isNull()) return mFormPixmapCache;
#endif
    QPixmap formMap(mParms.pixmapSize());
    formMap.fill(mParms.marginBackgroundColor());
    // -----start
    QPainter * formPainter = new QPainter(&formMap);
    formPainter->begin(&formMap);
    // -----Graph Background
    mParms.drawGraphBackground(formPainter);
    // -----Border
    formPainter->setPen(mParms.borderPen());
    formPainter->drawRect(mParms.borderDrawRect());
    formPainter->setPen(mParms.graphZeroPen());
    formPainter->drawLine(mParms.graphZeroLine());
    WANTDO("Ticks")
    // -----finish
    formPainter->end();
    return formMap;
}

QPixmap UnitRatioGraph::graphPixmap(VectorColumnSet * columnSet)
{
    TRACEFN()
    QPixmap graphMap = formPixmap();
    QPainter * painter = new QPainter(&graphMap);
    painter->begin(&graphMap);

    for (int x = 1; x <= 3; x++)
        if (columnSet->contains(VectorColumnRole::Column(x)))
            mParms.drawColumn(painter,
                columnSet->value(VectorColumnRole::Column(x)), x);

    TODO("More?");

    painter->end();
    return  graphMap;
}

UnitRatioGraph::Parms::Parms(const QVariantMap & settings)
{
    TRACEFN()
    set(settings);
}

void UnitRatioGraph::Parms::set(const QVariantMap & settings)
{
    TRACEFN()
    mSettings = settings;
}

void UnitRatioGraph::Parms::replace(const QString & key,
                                     const QVariant & setting)
{
    TRACEQFI << key << setting;
    mSettings.insert(key, setting);
}

void UnitRatioGraph::Parms::replace(const QVariantMap & settings)
{
    TRACEFN()
    foreach(QString key, settings.keys())
            replace(key, settings.value(key));
}

QVariant UnitRatioGraph::Parms::value(const QString & key,
                                const QVariant & defValue) const
{
    QVariant var = mSettings.value(key, defValue);
//    TRACEQFI << key << var;
    return var;
}

QSize UnitRatioGraph::Parms::pixmapSize() const
{
    TRACEFN()
    QRect gRect = graphRect();
    int height = gRect.height() + 2 * gRect.top();
    int width  = gRect.width() + 2 * gRect.left();
    QSize size(width, height);
    TRACE << size;
    return size;
}

QRect UnitRatioGraph::Parms::graphRect(void) const
{
    TRACEFN()
    int mxCoefs = maxCoefs();
    int mxVectors = maxVectors();
    int height = 2 * verticalScale() + 1;
    int width  = interGap() * mxCoefs + 1;
    width += intraGap() * (mxVectors - 1) * mxCoefs;
    width += graphBarThickness() * mxCoefs;
    int originOffsetWidth = marginWidth();
    originOffsetWidth += borderThickness();
    int originOffsetHeight = marginHeight();
    originOffsetWidth += RoundUp(value("BorderThickness", 3).toInt());
    QRect rect(QPoint(originOffsetWidth, originOffsetHeight), // topLeft
               QSize(width, height));
    TRACEQFI << "return" << rect;
    return rect;
}

QRect UnitRatioGraph::Parms::borderBoundRect(void) const
{
    TRACEFN()
    int thick = borderThickness();
    QRect rect = graphRect() + QMargins(thick, thick, thick, thick);
    TRACEQFI << "return" << rect;
    return rect;
}

QRect UnitRatioGraph::Parms::borderDrawRect(void) const
{
    TRACEFN()
    int thick = borderThickness();
    int half = RoundUp(thick / 2, true);
    QRect rect = graphRect() + QMargins(half, half, half, half);
    TRACEQFI << "return" << rect;
    return rect;
}

void UnitRatioGraph::Parms::drawGraphBackground(QPainter *painter)
{
    QColor bgbase = graphBaseBackground();
    QLine nzline = graphZeroLine();
    int vert = verticalScale();
    int thick = graphBarThickness();
    QRect graphrc = graphRect();
    painter->fillRect(graphrc, bgbase);
    QRect highposrc(graphrc.topLeft(),
                    QSize(graphrc.width(), vert / 2));
    QRect midposrc(QPoint(graphrc.left(), highposrc.bottom()),
                   QSize(graphrc.width(), 3 * vert / 10));
    QRect lowposrc(QPoint(graphrc.left(), midposrc.bottom()),
                   QSize(graphrc.width(), 2 * vert / 10 - thick));
    QRect nzposrc(QPoint(graphrc.left(), lowposrc.bottom()),
                   QSize(graphrc.width(), thick));
    QRect nznegrc(QPoint(nzline.x1(), nzline.y1() + 1),
                  QPoint(nzline.x2(), nzline.y2() + 1 + thick));
    QRect lownegrc(nznegrc.bottomLeft(),
                   QSize(graphrc.width(), 2 * vert / 10 - thick));
    QRect midnegrc(lownegrc.bottomLeft(),
                   QSize(graphrc.width(), 3 * vert / 10));
    QRect highnegrc(midnegrc.bottomLeft(),
                   QSize(graphrc.width(), vert / 2));
    QColor bghighpos = bgbase.lighter(105);
    QColor bgmidpos  = bgbase.lighter(110);
    QColor bglowpos  = bgbase.lighter(115);
    QColor bgnzpos   = bgbase.lighter(125);
    painter->fillRect(highposrc, bghighpos);
    painter->fillRect(midposrc, bgmidpos);
    painter->fillRect(lowposrc, bglowpos);
    painter->fillRect(nzposrc, bgnzpos);
    QColor bghighneg = bgbase.darker(125);
    QColor bgmidneg  = bgbase.darker(115);
    QColor bglowneg  = bgbase.darker(110);
    QColor bgnzneg   = bgbase.darker(105);
    painter->fillRect(highnegrc, bghighneg);
    painter->fillRect(midnegrc, bgmidneg);
    painter->fillRect(lownegrc, bglowneg);
    painter->fillRect(nznegrc, bgnzneg);
    TODO("Fix Edges");
}

void UnitRatioGraph::Parms::drawColumn(QPainter * painter,
                                        const VectorColumn & column,
                                        const int vecX)
{
    TRACEQFI << column.columnName() << vecX;
    for (int coefX = 0; coefX < maxCoefs(); ++coefX)
    {
        WANTDO("Shading?")
        QPen pen(column.baseBackgroundColor());
        painter->setPen(pen);
        QLine coefLine = graphLine(column.values().value(coefX),
                                   coefX, vecX);
        painter->drawLine(coefLine);
    }
}



int UnitRatioGraph::Parms::maxCoefs() const
{
    return value("MaxCoefs", 320).toInt();
}

int UnitRatioGraph::Parms::maxVectors() const
{
    return value("MaxVectors", 3).toInt();
}

int UnitRatioGraph::Parms::verticalScale() const
{
    return value("VerticalScale", 100).toInt();
}

int UnitRatioGraph::Parms::interGap() const
{
    return value("InterGap", 1).toInt();
}

int UnitRatioGraph::Parms::intraGap() const
{
    return value("IntraGap", 0).toInt();
}

int UnitRatioGraph::Parms::graphBarThickness() const
{
    return  RoundUp(value("BarThickness", 3).toInt());
}

QColor UnitRatioGraph::Parms::graphBaseBackground() const
{
    return QColor(value("GraphBaseBackgroundColor", "#9CF").toString());
}

int UnitRatioGraph::Parms::marginWidth() const
{
    return value("MarginWidth", 10).toInt();
}

int UnitRatioGraph::Parms::marginHeight() const
{
    return value("MarginHeight", 10).toInt();
}

int UnitRatioGraph::Parms::borderThickness() const
{
    return RoundUp(value("BorderThickness", 3).toInt());
}

QColor UnitRatioGraph::Parms::borderColor() const
{
    return QColor(value("BorderColor", "#006").toString());
}

QBrush UnitRatioGraph::Parms::borderBrush() const
{
    return QBrush(borderColor());
}

QPen UnitRatioGraph::Parms::borderPen() const
{
    return QPen(borderBrush(), borderThickness());
}

QColor UnitRatioGraph::Parms::marginBackgroundColor(void) const
{
    TRACEFN()
    QColor bgColor(value("MarginColor", "#FF9").toString());
    TRACE << bgColor;
    return bgColor;
}

QPoint UnitRatioGraph::Parms::graphOrigin() const
{
    QRect drawRect = borderDrawRect();
    int vertScale = verticalScale();
    int x = drawRect.left();
    int y = drawRect.top() + vertScale + 1;
    return QPoint(x, y);
}

int UnitRatioGraph::Parms::graphZeroY() const
{
    QRect drawRect = borderDrawRect();
    int vertScale = verticalScale();
    return drawRect.top() + vertScale + 1;
}

QLine UnitRatioGraph::Parms::graphZeroLine() const
{
    QRect drawRect = borderDrawRect();
    int y = graphZeroY();
    return QLine(drawRect.left(), y, drawRect.right(), y);
}

QPen UnitRatioGraph::Parms::graphZeroPen() const
{
    return QPen(borderColor());
}

QLine UnitRatioGraph::Parms::graphLine(const UnitFloat value,
                                        const int coefIndex,
                                        const int vectorIndex)
{
    TRACEQFI << value << coefIndex << vectorIndex;
    QLine line;
    QPoint org = graphOrigin();
    int height = int(value * qreal(verticalScale()));
    int coefXofs = interGap() * (coefIndex + 1);
    coefXofs += (intraGap() + graphBarThickness()) * vectorIndex;
    line.setP1(QPoint(org.x() + coefXofs, org.y()));
    line.setP2(QPoint(org.x() + coefXofs, org.y() + height));
    NEEDDO("check");
    TRACE << "return" << line;
    return QLine();
}

QPen UnitRatioGraph::Parms::graphPen(const QColor & color)
{
    QPen pen(QBrush(color), graphBarThickness());
    TRACEQFI << color << pen;
    return pen;
}

int UnitRatioGraph::Parms::RoundUp(const int value, const bool odd)
{
    int roundValue = value;
    roundValue >>= 1;
    roundValue <<= 1;
    roundValue += odd ? 1 : 2;
    TRACEQFI << value << odd << "return" << roundValue;
    return roundValue;
}
