#pragma once

#include <QObject>
#include "VectorColumn.h"

class VectorColumnObject : public QObject, public VectorColumn
{
    Q_OBJECT
public:
    explicit VectorColumnObject(const VectorColumn vc,
                                QObject * parent=nullptr);

signals:

};

