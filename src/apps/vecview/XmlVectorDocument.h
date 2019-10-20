#pragma once

#include <VectorDocument.h>

class XmlVectorDocument : public VectorDocument
{
    Q_OBJECT
public:
    XmlVectorDocument(MdiDocumentManager * parent=nullptr);
};

