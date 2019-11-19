// file: ./src/apps/vecview/VectorGraph.cpp
#include "VectorGraph.h"

#include <QBrush>
#include <QColor>
#include <QPen>

QList<QRgb> VectorGraph::smColors;

VectorGraph::VectorGraph(void)
{
    ctor();
}

VectorGraph::VectorGraph(const Vector::List vectors)
{
    foreach (Vector vector, vectors)
        append(vector);
    ctor();

}

void VectorGraph::ctor()
{
    if (smColors.isEmpty())
        generateColors();
}

int VectorGraph::append(const Vector &vector)
{
    mVectors.append(vector);
    return mVectors.size();
}

void VectorGraph::draw(const bool border)
{
    drawPath(border);
}

void VectorGraph::drawPath(const bool border)
{
    QRect rect(QPoint(0, 128),
               QSize(320 * mVectors.size() * mBarWidth, 256));
    mPath.clear();
    if (border)
    {
        QPen pen(QColor(0,0,0));
        QBrush brush(QColor(0xFF, 0xFF, 0xCC));
        mPath.addRect(rect);
        mPath.moveTo(QPoint(0,0));
        mPath.lineTo(QPoint(rect.width(), 0));
    }

    int r = 0, c = 0;
    int numCoef = mVectors.first().size();

    for (int i = 0; i < numCoef; ++i)
    {
        foreach (Vector vector, mVectors)
        {
            Vector::CoefValue coef = vector.at(i);
            r = int(coef * 128);
            for(int kw = 0; kw < mBarWidth; ++kw)
            {
                mPath.moveTo(c, 0);
                mPath.lineTo(c, r);
                ++c;
            }
        }
    }
}

QPixmap VectorGraph::pixmap() const
{

}

QImage VectorGraph::image(const QImage::Format format) const
{

}

void VectorGraph::generateColors()
{

}

QList<QRgb> VectorGraph::getSmColors()
{
    return smColors;
}

void VectorGraph::setSmColors(const QList<QRgb> &value)
{
    smColors = value;
}
