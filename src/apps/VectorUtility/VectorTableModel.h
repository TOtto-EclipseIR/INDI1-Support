#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include <QVariant>

#include "VectorObject.h"
class VectorObject;


class VectorTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    VectorTableModel(QObject * parent=nullptr);
    virtual int rowCount(const QModelIndex & parent=QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent=QModelIndex()) const;
    virtual QVariant data(const QModelIndex & mx,
                  const int role=Qt::DisplayRole) const;
public slots:
    void setup(const int rows);
    void appendVector(VectorObject * vector);

private:
    int cmIndexColumn = 0;
    int mNumRows = 320;
    VectorObject::List mVectors;
};

