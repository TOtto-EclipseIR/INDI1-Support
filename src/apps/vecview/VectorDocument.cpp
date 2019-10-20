#include "VectorDocument.h"

VectorDocument::VectorDocument(MdiDocumentManager * parent)
    : BaseMdiDocument(QString("Vector"), parent)
{
    setObjectName("VectorDocument");
}
