#pragma once

#include <QPair>
#include <QString>


class Vector
{
public:
    enum FileScope
    {
        nullScope   = 0,
        BaseLine    = 1,
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
        EyeLocation,
        NormalRecon,
        RawXml,
        sizeView
    };
/*
    enum Window
    {
        nullWindow = 0,
        BaseLine,
        SubjectOne,
        SubjectTwo,
        BaseOne,
        BaseTwo,
        OneTwo,
        BaseBoth,
        sizeWindow
    };
*/
    enum Columns
    {
        nullColumn = 0,
        BaseLineCol,
        SubjectOneCol,
        SubjectTwoCol,
        DeltaBaseOne,
        DeltaBaseTwo,
        DeltaOneTwo,
        RatioBaseOne,
        RatioBaseTwo,
        RatioOneTwo,
        sizeColumns
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

