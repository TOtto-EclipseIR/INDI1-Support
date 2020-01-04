#include "VectorTableModel.h"

#include <QModelIndex>
#include <QTimer>

#include "VectorObject.h"


VectorTableModel::VectorTableModel(QObject * parent)
    : QAbstractTableModel(parent)
    , mNumRows(320)
{
    setObjectName("VectorTableModel");
    QTimer::singleShot(100, this, SLOT(setup(320)));
}

int VectorTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mNumRows;
}

int VectorTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mVectors.size();
}

QVariant VectorTableModel::data(const QModelIndex &mx, const int role) const
{
    Q_UNUSED(role)
    QVariant result;
    if (mx.row() >= 0 && mx.row() < rowCount()
            && mx.column() >= 0 && mx.column() < columnCount())
        result.setValue(mVectors[mx.column()]->at(mx.row()));
    return result;
}

void VectorTableModel::setup(const int rows)
{
    mNumRows = rows;

    QModelIndex ix = createIndex(0, 0, this);
    beginInsertColumns(ix, 0, 0);
    insertColumns(0, 1, ix);
    endInsertColumns();
}


void VectorTableModel::appendVector(VectorObject * vector)
{
    mVectors.append(vector);
}
