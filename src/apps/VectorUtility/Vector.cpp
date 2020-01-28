#include "Vector.h"

Vector::Vector(void) {}

QString Vector::scopeString(const Vector::FileScope scope)
{
    switch (scope)
    {
    case nullScope:     return "{nullScope}";
    case Baseline:      return "BaseLine";
    case SubjectOne:    return "SubjectOne";
    case SubjectTwo:    return "SubjectTwo";
    default:            return QString("{?%1?}").arg(int(scope));
    }
}

QString Vector::viewString(const Vector::View view)
{
    switch (view)
    {
    case nullView:          return "{nullView}";
    case Summary:           return "Summary";
    case Grid:              return "Grid";
    case Graph:             return "Graph";
    case Reconstruction:    return "Reconstruction";
    case RawXml:            return "RawXml";
    default:                return QString("{?%1?}").arg(int(view));
    }
}

