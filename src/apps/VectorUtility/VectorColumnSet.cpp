#include "VectorColumnSet.h"

#include "Debug.h"

VectorColumnSet::VectorColumnSet(QObject * parent) :
    QObject(parent)
{
    TRACEFN()
    setObjectName("VectorColumnSet");
    CONNECT(this, SIGNAL(columnChangedRole(VectorColumn::Role)),
            this, SLOT(updateForChangedColumn(VectorColumn::Role)));
    CONNECT(this, &VectorColumnSet::columnsToUpdate,
            this, &VectorColumnSet::updateColumnList);
}

void VectorColumnSet::set(const VectorColumn & vc)
{
    TRACEQFI << vc.columnName();
    remove(vc.column());
    mColumnSet.insert(vc.column(), new VectorColumnObject(vc, this));
    emit columnChangedRole(vc.column());
    emit columnChangedRole(vc);
}

bool VectorColumnSet::contains(const VectorColumnRole::Column col) const
{
    bool yes = mColumnSet.contains(col);
    TRACEQFI << VectorColumn::columnName(col) << yes;
    return yes;
}


VectorColumn VectorColumnSet::value(const VectorColumnRole::Column col) const
{
    TRACEQFI << col;
    if ( ! mColumnSet.contains(col))
    {
        ERRORQFI << "does not contain" << col;
        return VectorColumn();
    }
    VectorColumnObject * pvco = mColumnSet.value(col);
    TSTALLOC(pvco);
    return VectorColumn(*pvco);
}

void VectorColumnSet::remove(const VectorColumnRole::Column col)
{
    if (contains(col))
    {
        VectorColumnObject * pvco = mColumnSet.value(col);
        TSTALLOC(pvco);
        pvco->deleteLater();
        mColumnSet.insert(col, nullptr);
    }
}

void VectorColumnSet::
    updateForChangedColumn(VectorColumnRole::Column changedCol)
{
    TRACEQFI << VectorColumn::columnName(changedCol);
    VectorColumnRole::ColumnList colList
            = VectorColumnRole::columnsForChanged(changedCol);
    TRACE << colList;
    emit columnsToUpdate(colList);
}

void VectorColumnSet::updateColumn(const VectorColumnRole::Column col)
{
    TRACEQFI << col;
    VectorColumnRole::Column firstCol  = VectorColumnRole::nullCol;
    VectorColumnRole::Column secondCol = VectorColumnRole::nullCol;
    NEEDDO("figeritout");
    if (contains(firstCol) && contains(secondCol))
    {
        VectorColumn firstVC  = value(firstCol);
        VectorColumn secondVC = value(secondCol);
        VectorColumn newVC(col, firstVC.rows());
        if (false)
            ;
        else if (newVC.isDelta())
            newVC.setDelta(firstVC, secondVC);
        else if (newVC.isRatio())
            newVC.setRatio(firstVC, secondVC);
        else
            WARNQFI << "Wierd Linkage not Delta or Ratio" << col;
        set(newVC);
    }
}

void VectorColumnSet::updateColumnList(
        VectorColumnRole::ColumnList cols)
{
    TRACEQFI << cols;
    if ( ! cols.isEmpty())
        updateColumn(cols.takeFirst());
    if ( ! cols.isEmpty()) emit columnsToUpdate(cols);
}

