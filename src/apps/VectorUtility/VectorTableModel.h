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
public slots:
    void setup(const int rows);
    void appendVector(VectorObject * vector);

private:
    int cmIndexColumn = 0;
    int mNumRows = 320;
    VectorObject::List mVectors;
};

