#pragma once

#include <QObject>
#include <QAbstractItemModel>

#include <QList>
#include <QSize>

#include "UnitFloat.h"
#include "Vector.h"
#include "VectorObject.h"

class VectorItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit VectorItemModel(QObject * parent=nullptr);
    virtual QVariant data(const QModelIndex & index,
                   int role=Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column,
         const QModelIndex & parent=QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex & index) const;
    virtual int rowCount(const QModelIndex & parent=QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent=QModelIndex()) const;
    bool isValidIndex(const QModelIndex & mx) const;
    bool set(const QModelIndex & mx,
             const UnitFloat value,
             const int role=Qt::DisplayRole);

public slots:
    void set(VectorObject * vector);
    void update(void);


signals:


private:
    QList<VectorObject *> mVectors;
    bool mCalculatedColumnsDirty = true;
};

