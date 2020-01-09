#pragma once

#include <QObject>
#include <QAbstractTableModel>

#include <QList>
#include <QMap>
#include <QVariant>

#include "UnitFloatVector.h"
#include "VectorObject.h"


class VectorTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    typedef QList<double> FloatVector;

public:
    VectorTableModel(const int rows, QObject * parent=nullptr);
    int floatMapCount(void) const
    { return mFloatMap.size(); }
    int unitMapCount(void)
    { return mUnitMap.size(); }

public: // virtual
    virtual int rowCount(const QModelIndex & parent=QModelIndex()) const;
    virtual int columnCount(const QModelIndex & parent=QModelIndex()) const;
    virtual QVariant data(const QModelIndex & mx,
                  const int role=Qt::DisplayRole) const;
    virtual bool setHeaderData(int section,
                               Qt::Orientation orientation,
                               const QVariant & value,
                               int role=Qt::EditRole);

protected slots:
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }

public slots:
    void setup(void);

signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

protected:
    void set(VectorObject * vector);
    void recalculate(void);
    void recalculate(const Vector::FileScope scope);
    void recalculate(const VectorObject::Columns column);

private:
    int cmIndexColumn = 0;
    int mNumRows = 320;
    QMap<VectorObject::Columns, FloatVector> mFloatMap;
    QMap<Vector::FileScope, UnitFloatVector> mUnitMap;
};

