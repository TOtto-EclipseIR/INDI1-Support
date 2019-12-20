#include "Vector.h"

Vector::Vector(void) {}

QString Vector::scopeString(const Vector::FileScope scope)
{
    switch (scope)
    {
    case nullScope:         return "{null}";
    case BaseLineFile:      return "BaseLine";
    case SubjectOneFile:    return "SubjectOne";
    case SubjectTwoFile:    return "SubjectTwo";
    default:                return "{???}";
    }
}

QString Vector::viewString(const Vector::View view)
{
    switch (view)
    {
    case nullView:      return "{null}";
    case Summary:       return "Summary";
    case Grid:          return "Grid";
    case Graph:         return "Graph";
    case EyeLocation:   return "EyeLocation";
    case NormalRecon:   return "NormalRecon";
    case RawXml:        return "RawXml";
    default:            return "{???}";
    }
}

QString Vector::windowString(const Vector::Window window)
{
    switch (window)
    {
    case nullWindow:    return "{null}";
    case BaseLine:      return "BaseLine";
    case SubjectOne:    return "SubjectOne";
    case SubjectTwo:    return "SubjectTwo";
    case OneTwo:        return "OneTwo";
    case BaseOne:       return "BaseOne";
    case BaseTwo:       return "BaseTwo";
    case BaseBoth:      return "BaseBoth";
    case sizeWindow:    return "{???}";
    }
    return QString();
}

QString Vector::windowViewString(const Vector::WindowView windowView)
{
    return windowString(windowView.first)
            +"/"+viewString(windowView.second);
}

bool Vector::windowIncludesScope(const Vector::Window window,
                                 const Vector::FileScope scope)
{
    switch (scope)
    {
    case BaseLineFile:
        switch (window)
        {
        case BaseLine:
        case BaseOne:
        case BaseTwo:
        case BaseBoth:  return true;
        default:        return false;
        }


    case SubjectOneFile:
        switch (window)
        {
        case SubjectOne:
        case OneTwo:
        case BaseOne:
        case BaseBoth:  return true;
        default:        return false;
        }

    case SubjectTwoFile:
        switch (window)
        {
        case SubjectTwo:
        case OneTwo:
        case BaseTwo:
        case BaseBoth:  return true;
        default:        return false;
        }

    default:
        break;
    }
    return false;
}
