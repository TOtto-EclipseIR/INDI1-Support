#include "VectorColumnRole.h"


#include "Debug.h"

DualMap<VectorColumnRole::Column, QString>
        VectorColumnRole::smColumnNameDMap;
DualMap<VectorColumnRole::Linkage,
        VectorColumnRole::Column> VectorColumnRole::smLinkColumnDMap;


VectorColumnRole::VectorColumnRole(void)
{
    ctor();
}

VectorColumnRole::VectorColumnRole(const VectorColumnRole::Column col)
    : mColumn(col)
    , mLinkage(link(mColumn))
{
    ctor();
}

void VectorColumnRole::ctor(void)
{
    if (smColumnNameDMap.isEmpty())
    {
        smColumnNameDMap.insertUnique(BaselineCol,      "Baseline");
        smColumnNameDMap.insertUnique(SubjectOneCol,    "Subject One");
        smColumnNameDMap.insertUnique(SubjectTwoCol,    "Subject Two");
        smColumnNameDMap.insertUnique(DeltaBaseOneCol,  "Delta BaseOne");
        smColumnNameDMap.insertUnique(DeltaBaseTwoCol,  "Delta BaseTwo");
        smColumnNameDMap.insertUnique(DeltaOneTwoCol,   "Delta OneTwo");
        smColumnNameDMap.insertUnique(RatioBaseOneCol,  "Ratio BaseOne");
        smColumnNameDMap.insertUnique(RatioBaseTwoCol,  "Ratio BaseTwo");
        smColumnNameDMap.insertUnique(RatioOneTwoCol,   "Ratio OneTwo");
        smColumnNameDMap.insertUnique(nullCol,          "{null}");
    }

    if (smLinkColumnDMap.isEmpty())
    {
        smLinkColumnDMap.insertUnique(BaselineLink, columnLink(BaselineLink));
        smLinkColumnDMap.insertUnique(SubjectOneLink, columnLink(SubjectOneLink));
        smLinkColumnDMap.insertUnique(SubjectTwoLink, columnLink(SubjectTwoLink));
        smLinkColumnDMap.insertUnique(DeltaBaseOneLink, columnLink(DeltaBaseOneLink));
        smLinkColumnDMap.insertUnique(DeltaBaseTwoLink, columnLink(DeltaBaseTwoLink));
        smLinkColumnDMap.insertUnique(DeltaOneTwoLink, columnLink(DeltaOneTwoLink));
        smLinkColumnDMap.insertUnique(RatioBaseOneLink, columnLink(RatioBaseOneLink));
        smLinkColumnDMap.insertUnique(RatioBaseTwoLink, columnLink(RatioBaseTwoLink));
        smLinkColumnDMap.insertUnique(RatioOneTwoLink, columnLink(RatioOneTwoLink));
    }

    WANTDO("Check expected relationships with int types");
}

void VectorColumnRole::set(const VectorColumnRole::Column col)
{
    mColumn = col;
    mLinkage = link(mColumn);
}

VectorColumnRole::Column VectorColumnRole::column() const
{
    return mColumn;
}

QString VectorColumnRole::columnName() const
{
    return columnName(column());
}

void VectorColumnRole::nullify()
{
    mColumn = nullCol;
    mLinkage = nullLink;
}

bool VectorColumnRole::isDelta() const
{
    return link() & DeltaFlag;
}

bool VectorColumnRole::isRatio() const
{
    return link() & RatioFlag;
}

int VectorColumnRole::numColumns()
{
    return sizeCol;
}

QString VectorColumnRole::columnName(
            const VectorColumnRole::Column col)
{
    return smColumnNameDMap.at(col);
}

VectorColumnRole::ColumnList
    VectorColumnRole::columnsForChanged(
        const VectorColumnRole::Column col)
{
    TRACEQFI << columnName(col);
    VectorColumnRole::ColumnList colList;

    NEEDDO("scan for 'involved'");

    TRACE << colList;
    return colList;
}

VectorColumnRole::Linkage VectorColumnRole::link() const
{
    return mLinkage;
}

VectorColumnRole::ColumnList VectorColumnRole::allColumns()
{
    VectorColumnRole::ColumnList list = smColumnNameDMap.keys();
    list.removeOne(nullCol);
    return list;
}

VectorColumnRole::Linkage VectorColumnRole::link(const Column col)
{
    return smLinkColumnDMap.at(col);
}

VectorColumnRole::Column
    VectorColumnRole::columnLink(const VectorColumnRole::Linkage link)
{
    return VectorColumnRole::Column(link & ColumnMask);
}

VectorColumnRole::LinkList VectorColumnRole::linkList()
{
    return smLinkColumnDMap.keys();
}

VectorColumnRole::Column
    VectorColumnRole::argCol(const bool first,
                             const VectorColumnRole::Column col)
{
    TRACEQFI << first << col;
    NEEDDO("figureitout");
    NEEDRTN(VectorColumnRole::Column());
}

VectorColumnRole::Column
    VectorColumnRole::firstArgCol(const VectorColumnRole::Column col)
{
    TRACEQFI  << col;
    NEEDDO("figureitout");
    NEEDRTN(VectorColumnRole::Column());
}

VectorColumnRole::Column
    VectorColumnRole::secondArgCol(const VectorColumnRole::Column col)
{
    TRACEQFI << col;
    NEEDDO("figureitout");
    NEEDRTN(VectorColumnRole::Column());
}
