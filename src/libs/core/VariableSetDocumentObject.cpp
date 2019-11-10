#include "VariableSetDocumentObject.h"

VariableSetDocumentObject::
    VariableSetDocumentObject(VariableSetDocument * doc,
                              QObject *parent)
    : ErrorStatusObject(parent)
    , cmpDocument(doc)
{
    setObjectName(QString("VariableSetDocumentObject:%1")
                  .arg(cmpDocument->fileName()));
}

bool VariableSetDocumentObject::parseDomDocument(QByteArray ba)
{
    return cmpDocument->parseDomDocument(ba);
}
