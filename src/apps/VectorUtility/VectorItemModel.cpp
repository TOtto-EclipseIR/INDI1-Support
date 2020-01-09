#include "VectorItemModel.h"

#include "UnitFloatLabel.h"

VectorItemModel::VectorItemModel(QObject * parent)
    : QAbstractItemModel(parent)
{
    setObjectName("VectorItemModel");

    mVectors.reserve(VectorObject::columnCount());
    while (mVectors.size() < VectorObject::columnCount())
        mVectors << nullptr;
}

QVariant VectorItemModel::data(const QModelIndex & index,
                               int role) const
{
    Q_UNUSED(role)
    if ( ! isValidIndex(index)) return QVariant();
    VectorObject * vector = mVectors.at(index.column());
//    UnitFloat uf = vector->at(index.column());
    //UnitFloatLabel ufl(uf);
    // TODO handle role
    //return ufl.text();
    return QVariant();
}

QModelIndex VectorItemModel::index(int row, int column,
                                   const QModelIndex &parent) const
{
    (void)(parent);
    return createIndex(row, column);
}

QModelIndex VectorItemModel::parent(const QModelIndex & index) const
{
    return index.parent();
}

int VectorItemModel::rowCount(const QModelIndex & parent) const
{
    (void)(parent);
    return mVectors.first()->coefVector().size();
}

int VectorItemModel::columnCount(const QModelIndex & parent) const
{
    (void)(parent);
    return mVectors.size();
}

bool VectorItemModel::isValidIndex(const QModelIndex & mx) const
{
    return mx.row() >= 0 && mx.row() < rowCount()
            && mx.column() >= 0 && mx.column() < columnCount();
}

bool VectorItemModel::set(const QModelIndex & mx,
                          const UnitFloat value,
                          const int role)
{
    mCalculatedColumnsDirty =  true;
    emit dataChanged(mx, mx);
    return setData(mx, QVariant(value), role);
}

void VectorItemModel::set(VectorObject * vector)
{
    Vector::FileScope scope = vector->scope();
    int row = 0, col = int(scope);
    foreach (UnitFloat uf, vector->coefVector().values())
    {
        QModelIndex mx = index(row, col);
        set(mx, uf);
    }

}

void VectorItemModel::update()
{
    // TODO
}
