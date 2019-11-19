#include "Drawing.h"

Drawing::Drawing(void)
    : mPainter(&mPicture)
{

}

Drawing::Drawing(const QRect & rect,
                 const QPen & pen,
                 const QBrush & brush)
    : mPainter(&mPicture)
{
    mPainter.begin(mPainter.device());
    mPainter.setPen(pen);
    mPainter.setBrush(brush);
    mPainter.drawRect(rect);
    mPainter.end();
}

void Drawing::ctor()
{

}
