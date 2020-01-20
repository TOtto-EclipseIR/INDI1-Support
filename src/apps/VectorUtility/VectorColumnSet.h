#pragma once

#include <QObject>

#include <QMap>

#include "VectorColumn.h"
#include "VectorColumnObject.h"
#include "VectorObject.h"

class VectorColumnSet : public QObject
{
    Q_OBJECT
public:
    explicit VectorColumnSet(QObject * parent=nullptr);
    void set(const VectorColumn & vc);
    bool contains(const VectorColumnRole::Column col) const;

    VectorColumn value(const VectorColumnRole::Column col) const;
    VectorColumn & at(const VectorColumnRole::Column col);
    VectorColumn & operator [](const VectorColumnRole::Column col)
    { return at(col); }
    void remove(const VectorColumnRole::Column col);


public slots:
    void updateForChangedColumn(VectorColumnRole::Column changedCol);

protected slots:
    void updateColumn(VectorColumnRole::Column col);
    void updateColumnList(VectorColumnRole::ColumnList cols);

signals:
    void columnsToUpdate(VectorColumnRole::ColumnList cols);
    void columnChangedRole(VectorColumnRole::Column changedCol);
    void columnChangedRole(VectorColumn changedColumn);


private:
    QMap<VectorColumnRole::Column, VectorColumnObject *> mColumnSet;
    QMap<QString, ForeBackGroundColors> mBaseColors;

};

