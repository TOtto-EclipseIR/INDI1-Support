#pragma once

#include "../base/ErrorStatusObject.h"
#include "VariableSetDocument.h"



class VariableSetDocumentObject : public ErrorStatusObject
{
    Q_OBJECT
public:
    explicit VariableSetDocumentObject(VariableSetDocument * doc,
                                       QObject * parent=nullptr);
    VariableSetDocumentObject(const QFileInfo & fi,
                              QObject * parent=nullptr);

public slots:
    bool readFile(QFileInfo fi) {}
    bool parseDomDocument(QByteArray ba);

signals:
    void fileRead(bool success);

private:
    VariableSetDocument * cmpDocument=nullptr;
};

