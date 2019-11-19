// file: ./src/apps/vecview/VectorGraph.h
#pragma once

#include "../libs/gui/Drawing.h"

#include <QBrush>
#include <QImage>
#include <QList>
#include <QPen>
#include <QPicture>
#include <QPixmap>
#include <QRgb>


#include "Vector.h"



class VectorGraph : public Drawing
{
public:
    VectorGraph(void);
    VectorGraph(const Vector::List vectors);
    void ctor(void);

    int append(const Vector & vector);
    void setBarWidth(const int w)
    { mBarWidth = w; }

    void draw(const bool border=true);
    void drawPath(const bool border=false);

    QPainterPath path(void) const
    { return mPath; }
    QPicture picture(void) const;
    QPixmap pixmap(void) const;
    QImage image(const QImage::Format format) const;

public: // static
    static QList<QRgb> getSmColors();
    static void setSmColors(const QList<QRgb> &value);

private: // static
    static void generateColors(void);

private:
    Vector::List mVectors;
    int mBarWidth=1;
    QPainterPath mPath;


private: // static
    static QList<QRgb> smColors;



};

