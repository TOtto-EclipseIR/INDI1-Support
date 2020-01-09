#include "VectorTableModel.h"

#include <QModelIndex>
#include <QTimer>

#include "Debug.h"
#include "VectorObject.h"


VectorTableModel::VectorTableModel(const int rows, QObject * parent)
    : QAbstractTableModel(parent)
{
    TRACEFN()
    setObjectName("VectorTableModel");
    emit ctorFinished(this);
}

int VectorTableModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return mMatrix.rowCount();
}

int VectorTableModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return mMatrix.colCount();
}

QVariant VectorTableModel::data(const QModelIndex & mx,
                                const int role) const
{
    Q_UNUSED(role)
    QVariant result = mMatrix.value(
                VariantMatrix::Index(mx.row(), mx.column()));
    TRACEQFI << mx.row() << mx.column() << result;
    return result;
}

void VectorTableModel::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    QTimer::singleShot(100, this, &VectorTableModel::setup);
}

void VectorTableModel::setup(void)
{
    TRACEFN()
    QModelIndex mx = createIndex(0, 0);
    beginInsertColumns(mx, 0, columnCount(mx));
    insertColumns(0, columnCount(mx), mx);
    endInsertColumns();
    beginInsertRows(mx, 0, rowCount(mx));
    insertRows(0, rowCount(), mx);
    endInsertRows();

    setHeaderData(VectorObject::nullColumn,         Qt::Horizontal, "Index");
    setHeaderData(VectorObject::BaseLineCol,        Qt::Horizontal, "Base Line");
    setHeaderData(VectorObject::SubjectOneCol,      Qt::Horizontal, "Subject\nOne");
    setHeaderData(VectorObject::SubjectTwoCol,      Qt::Horizontal, "Subject Two");
    setHeaderData(VectorObject::DeltaBaseOneCol,    Qt::Horizontal, "Delta BaseOne");
    setHeaderData(VectorObject::DeltaBaseTwoCol,    Qt::Horizontal, "Delta BaseTwo");
    setHeaderData(VectorObject::DeltaOneTwoCol,     Qt::Horizontal, "Delta OneTwo");
    setHeaderData(VectorObject::RatioBaseOneCol,    Qt::Horizontal, "Ratio BaseOne");
    setHeaderData(VectorObject::RatioBaseTwoCol,    Qt::Horizontal, "Ratio BaseTwo");
    setHeaderData(VectorObject::RatioOneTwoCol,     Qt::Horizontal, "Ratio OneTwo");
    emit headerDataChanged(Qt::Horizontal,
                           VectorObject::nullColumn,
                           VectorObject::RatioOneTwoCol);
    finishSetup(this);
}

void VectorTableModel::set(const Vector::FileScope scope,
                           UnitFloatVector coefs)
{
    TRACEQFI << Vector::scopeString(scope);
    int rows = mMatrix.rowCount();
    coefs.resize(rows);
    VariantMatrix::Index ix;
    ix.setCol(int(scope));
    for (int row = 0; row < rows; ++row)
    {
        ix.setRow(row);
        mMatrix.set(ix, QVariant(coefs.at(row)));
    }
    recalculate(scope);
}


void VectorTableModel::set(VectorObject * vector)
{
    TRACEQFI << "TODO" << vector->objectName() << vector->vectorSize();
    mVectorMap.insert(vector->scope(), vector);
    set(vector->scope(), vector->coefVector());
}

void VectorTableModel::recalculate(void)
{
    TRACEFN()
    for(int scope = Vector::BaseLine;
        scope < Vector::sizeScope;
        ++scope)
    {
        recalculate(Vector::FileScope(scope));
    }
    for(int column = VectorObject::DeltaBaseOneCol;
        column < VectorObject::sizeColumns;
        ++column)
    {
        recalculate(VectorObject::Columns(column));
    }
}

void VectorTableModel::recalculate(const Vector::FileScope scope)
{
    TRACEQFI << "TODO";
}

void VectorTableModel::recalculate(const VectorObject::Columns column)
{
    TRACEQFI << "TODO";

}
