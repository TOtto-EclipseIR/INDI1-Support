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
