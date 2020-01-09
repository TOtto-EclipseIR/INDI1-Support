#include "VectorTableModel.h"

#include <QModelIndex>
#include <QTimer>

#include "Debug.h"
#include "VectorObject.h"


VectorTableModel::VectorTableModel(const int rows, QObject * parent)
    : QAbstractTableModel(parent)
    , mNumRows(rows)
{
    TRACEFN()
    setObjectName("VectorTableModel");
    connect(this, &VectorTableModel::ctorFinished,
            this, &VectorTableModel::startSetup);
    emit ctorFinished(this);
}

int VectorTableModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return mNumRows;
}

int VectorTableModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent)
    return VectorObject::sizeColumns;
}

QVariant VectorTableModel::data(const QModelIndex & mx,
                                const int role) const
{
    TRACEQFI << mx.row() << mx.column();
    Q_UNUSED(role)
    QVariant result;
    double value = qQNaN();
    if (mx.column() >= 0 && mx.column() < Vector::sizeScope)
    {
        Vector::FileScope scope = Vector::FileScope(mx.column());
        value = mUnitMap[scope].at(mx.row());
    }
    else if (mx.column() >= Vector::sizeScope
             && mx.column() < VectorObject::sizeColumns)
    {
        VectorObject::Columns column = VectorObject::Columns(mx.column());
        value = mFloatMap[column].at(mx.row());
    }
    if ( ! qIsNaN(value))
        result.setValue(value);
    return result;
}

bool VectorTableModel::setHeaderData(int section,
                                     Qt::Orientation orientation,
                                     const QVariant & value,
                                     int role)
{
    TRACEQFI << section << value;
    emit headerData(section, orientation, role);
    return QAbstractTableModel::setHeaderData(section,
                                              orientation,
                                              value,
                                              role);
}


void VectorTableModel::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    QTimer::singleShot(100, this, SLOT(setup));
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


void VectorTableModel::set(VectorObject * vector)
{
    TRACEQFI << vector->objectName() << vector->vectorSize();
    mUnitMap.insert(vector->scope(), vector->coefVector());
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
