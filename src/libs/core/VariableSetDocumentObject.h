#pragma once

#include "../base/ErrorStatusObject.h"
#include "VariableSetDocument.h"



class VariableSetDocumentObject : public ErrorStatusObject
{
    Q_OBJECT
public:
    explicit VariableSetDocumentObject(VariableSetDocument * doc,
                                       QObject * parent=nullptr);

public slots:
    bool parseDomDocument(QByteArray ba);

signals:

private:
    VariableSetDocument * cmpDocument=nullptr;
};

