#pragma once

#include <QObject>
#include <QAbstractTableModel>

#include <QList>
#include <QMap>
#include <QVariant>

#include "UnitFloatVector.h"
#include "VariantMatrix.h"
#include "Vector.h"
#include "VectorObject.h"


class VectorTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    typedef QList<double> FloatVector;

public:
    VectorTableModel(const int rows, QObject * parent=nullptr);
    void set(VectorObject * vector);
    VectorObject * vector(const Vector::FileScope scope)
    { return mVectorMap.value(scope); }
    void openVectorFile(Vector::FileScope scope,
                        QString fileName);
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }

public: // virtual
    virtual int rowCount(const QModelIndex & parent=QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent=QModelIndex()) const;
    virtual QVariant data(const QModelIndex & mx,
                  const int role=Qt::DisplayRole) const;

public slots:
    void setup(void);

signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

protected:
    void recalculate(void);
    void recalculate(const Vector::FileScope scope);
    void recalculate(const VectorObject::Columns column);

private:
    int mNumRows=00;
    VariantMatrix mMatrix;
    QMap<Vector::FileScope, VectorObject *> mVectorMap;
};

