#include "VariableSetDocumentObject.h"

#include "../base/Debug.h"

VariableSetDocumentObject::
    VariableSetDocumentObject(VariableSetDocument * doc,
                              QObject *parent)
    : ErrorStatusObject(parent)
    , cmpDocument(doc)
{
    TRACEFN()
    setObjectName(QString("VariableSetDocumentObject:%1")
                  .arg(cmpDocument->fileName()));
}

bool VariableSetDocumentObject::parseDomDocument(QByteArray ba)
{
    TRACEFN()
    return cmpDocument->parseDomDocument(ba);
}
