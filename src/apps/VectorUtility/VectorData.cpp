#include "VectorData.h"

DEFINE_DATAPROPS(VectorData, VectorDataData)

void VectorData::ctor(void)
{ mScope = Vector::FileScope(getScopeInt()); }
void VectorData::dtor(void) {} // ditto dtor

QString VectorData::title() const
{
    return getFileInfo().completeBaseName();
}
