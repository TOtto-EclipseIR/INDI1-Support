#include "VectorColumnObject.h"

VectorColumnObject::VectorColumnObject(const VectorColumn vc,
                                       QObject *parent)
    : QObject(parent)
    , VectorColumn(vc)
{
    setObjectName("VectorColumnObject:"+ vc.columnName());
}
