// file: ./src/apps/vecview/Vector.h
#pragma once

#include <QList>
#include <QVector>

#include "MetaVector.h"

class Vector
{
public:
    typedef qreal CoefValue;
    typedef QVector<CoefValue> CoefVector;
    typedef QList<Vector> List;

public:
    Vector(void);

private:
    MetaVector mMetaVector;
    CoefVector mCoefVector;
};

