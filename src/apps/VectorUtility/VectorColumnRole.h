// File: VectorColumnRole
#pragma once

#include <QMap>
#include <QString>

#include "DualMap.h"
#include "Vector.h"

class VectorColumnRole
{
public:
    enum Column
    {
        nullCol = 0,
        BaselineCol = Vector::Baseline,
        SubjectOneCol = Vector::SubjectOne,
        SubjectTwoCol = Vector::SubjectTwo,
        DeltaBaseOneCol,
        DeltaBaseTwoCol,
        DeltaOneTwoCol,
        RatioBaseOneCol,
        RatioBaseTwoCol,
        RatioOneTwoCol,
        sizeCol
    };
    typedef QList<Column> ColumnList;

    enum Option
    {
        noOption            = 0,
    };
    Q_DECLARE_FLAGS(Options, Option)

    enum Flag
    {
        noFlag              = 0,
        BaseFirstFlag       = 0x00010000,
        OneFirstFlag        = 0x00020000,
        OneSecondFlag       = 0x00002000,
        TwoSecondFlag       = 0x00004000,
        BaselineFlag        = 0x00100000,
        SubjectOneFlag      = 0x00200000,
        SubjectTwoFlag      = 0x00400000,
        ScopeFlag           = 0x01000000,
        DeltaFlag           = 0x10000000,
        RatioFlag           = 0x20000000,
        UnitFloatFlag       = 0x08000000,
    };
    Q_DECLARE_FLAGS(Flags, Flag)

protected:
    enum Masks
    {
        ColumnMask      = 0x000000FF,
        OperationMask   = 0x78000000,
        ScopeMask       = 0x00F00000,
        FirstArgMask    = 0x000F0000,
        SecondArgMask   = 0x0000F000,
    };

    enum Linkage
    {
        nullLink            = 0,
        BaselineLink        = 0x01100001,
        SubjectOneLink      = 0x01200002,
        SubjectTwoLink      = 0x01400003,
        DeltaBaseOneLink    = 0x10012004,
        DeltaBaseTwoLink    = 0x10014005,
        DeltaOneTwoLink     = 0x10024006,
        RatioBaseOneLink    = 0x20012007,
        RatioBaseTwoLink    = 0x20014008,
        RatioOneTwoLink     = 0x20024009,
    };
    typedef QList<Linkage> LinkList;

public:
    VectorColumnRole(void);
    VectorColumnRole(const Column col);
    void ctor(void);

    void set(const Column col);
    Column column(void) const;
    Linkage link(void) const;
    QString columnName(void) const;
    void nullify(void);
    bool isNull(void) const
    { return nullCol == mColumn; }
    bool isValid(void) const;
    bool isDelta(void) const;
    bool isRatio(void) const;

public: // static
    static bool isValid(const Column col);
    static int numColumns(void);
    static QString columnName(const Column col);
    static Column columnFor(const QString & name);
    static ColumnList allColumns(void);
    static ColumnList columnsForChanged(const Column col);

protected:
    Column columnFlag(void) const;
    Flag operationFlag(void) const;
    Flag firstArgFlag(void) const;
    Column secondArgFlag(void) const;

protected: // static
    static Linkage link(const Column col);
    static LinkList links(void);
    static Column columnLink(const Linkage link);
    static Column columnFlag(const Linkage link);
    static Flag operationFlag(const Linkage link);
    static Flag firstArgFlag(const Linkage link);
    static Flag secondArgFlag(const Linkage link);
    static LinkList linkList(void);
    static Column argCol(const bool first, const Column col);
    static Column firstArgCol(const Column col);
    static Column secondArgCol(const Column col);

private:
    Column mColumn=nullCol;
    Linkage mLinkage=nullLink;

private: // static
    static DualMap<Column, QString> smColumnNameDMap;
    static DualMap<Linkage, Column> smLinkColumnDMap;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(VectorColumnRole::Flags)
Q_DECLARE_OPERATORS_FOR_FLAGS(VectorColumnRole::Options)
