#pragma once

#include <QPair>
#include <QString>


class Vector
{
public:
    enum FileScope
    {
        nullScope   = 0,
        Baseline    = 1,
        SubjectOne  = 2,
        SubjectTwo  = 3,
        sizeScope
    };

    enum View
    {
        nullView = 0,
        Home,
        Summary,
        Grid,
        Graph,
        Reconstruction,
        RawXml,
        sizeView
    };

    //typedef QPair<Window, View> WindowView;

public:
    Vector(void);

public: // static
    static QString scopeString(const FileScope scope);
    static QString viewString(const View view);
    /*
    static QString windowString(const Window window);
    static QString windowViewString(const WindowView windowView);
    static bool windowIncludesScope(const Window window,
                                    const FileScope scope);
                                    */
};

