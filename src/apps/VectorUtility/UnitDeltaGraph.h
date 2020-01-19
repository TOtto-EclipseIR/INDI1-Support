#pragma once

#include <QBrush>
#include <QColor>
#include <QLine>
#include <QMargins>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QString>
#include <QVariant>
#include <QVariantMap>
#include <QVector>

#include "VectorColumnSet.h"

class UnitDeltaGraph
{
public:
    class Parms
    {
    public:
        Parms(void) {}
        Parms(const QVariantMap & settings);
        void set(const QVariantMap & settings);
        void replace(const QString & key, const QVariant & setting);
        void replace(const QVariantMap & settings);
        QVariant value(const QString & key,
                       const QVariant & defValue=QVariant()) const;

        QSize pixmapSize(void) const;
        QRect graphRect(void) const;
        QRect borderBoundRect(void) const;
        QRect borderDrawRect(void)const;

        void drawGraphBackground(QPainter * painter);
        void drawColumn(QPainter * painter, const VectorColumn & column, const int vecX);

        int maxCoefs(void) const;
        int maxVectors(void) const;
        int verticalScale(void) const;
        int interGap(void) const;
        int intraGap(void) const;
        int graphBarThickness(void) const;
        QColor graphBaseBackground(void) const;
        int marginWidth(void) const;
        int marginHeight(void) const;
        int borderThickness(void) const;
        QColor borderColor(void) const;
        QBrush borderBrush(void) const;
        QPen borderPen(void) const;
        QColor marginBackgroundColor(void) const;
        QPoint graphOrigin(void) const;
        int graphZeroY(void) const;
        QLine graphZeroLine(void) const;
        QPen graphZeroPen(void) const;
        QLine graphLine(const UnitFloat value,
                        const int coefIndex,
                        const int vectorIndex=0);
        QPen graphPen(const QColor & color);


    public: // static
        static int RoundUp(const int value, const bool odd=true);

    private:
        QVariantMap mSettings;
    };

public:
    UnitDeltaGraph(void);
    void configure(const QVariantMap & settings);
    void clearFormCache(void);
    void clearGraphCache(void);
    void clearDataCache(void);
    void updateData(void);
    QPixmap formPixmap(void);
    QPixmap graphPixmap(VectorColumnSet * columnSet);

private:
    Parms mParms;
    QPixmap mFormPixmapCache;
    QPixmap mGraphPixmapCache;
};

