#include "VectorItemModel.h"

#include "UnitFloatLabel.h"

VectorItemModel::VectorItemModel(const QSize size, QObject * parent)
    : QAbstractItemModel(parent)
{
    setObjectName("VectorItemModel");

    mVectors.reserve(Vector::sizeColumns);
    while (mVectors.size() < Vector::sizeColumns)
        mVectors << nullptr;
}

QVariant VectorItemModel::data(const QModelIndex & index,
                               int role) const
{
    if ( ! isValid(index)) return QVariant();
    VectorObject * vector = mVectors.at(index.column());
    UnitFloat uf = vector->at(index.column());
    UnitFloatLabel ufl(uf);
    // TODO handle role
    return ufl.text();
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

bool VectorItemModel::isValid(const QModelIndex ix) const
{

}

bool VectorItemModel::set(const QModelIndex &ix, const QVariant value, int role)
{

}

void VectorItemModel::set(VectorObject *vector)
{

}

void VectorItemModel::update()
{

}
