// file: ./src/apps/vecview/VectorGraph.h
#pragma once

#include "../libs/gui/Drawing.h"

#include <QRgb>

#include "Vector.h"

class VectorGraph : public Drawing
{
public:
    VectorGraph(void);
    VectorGraph(const Vector::List vectors);

};

