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
    CoefValue at(const int x) const
    { return mCoefVector.at(x); }
    int size(void) const
    { return mCoefVector.size(); }
    CoefValue & operator [] (const int x)
    { return mCoefVector[x]; }

private:
    MetaVector mMetaVector;
    CoefVector mCoefVector;
};

