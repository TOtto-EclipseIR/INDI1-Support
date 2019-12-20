#pragma once

#include <QObject>
#include <QAbstractTableModel>

class VectorTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    VectorTableModel(QObject * parent=nullptr);
};

