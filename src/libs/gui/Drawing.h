// file: ./src/libs/gui/Drawing.h
#pragma once
#include "Gui.h"

#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QPicture>



class GUI_EXPORT Drawing
{
public:
    Drawing(void);
    Drawing(const QRect & rect,
            const QPen & pen=QPen(),
            const QBrush & brush=QBrush());
    void ctor(void);

private:
    QPicture mPicture;
    QPainter mPainter;
};

