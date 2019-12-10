#pragma once
#include "Core.h"

#include "../exe/BaseDocumentObject.h"

#include <QSharedDataPointer>
#include "../base/DataProperty.h"

#include <QBuffer>
#include <QDataStream>
#include <QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QJsonDocument>
#include <QTextStream>
#include <QVariant>

#include "VariableSet.h"

#define VSDOCUMENT_DATAPROPS(TND) \
    TND(QDomDocument, DomDocument, QDomDocument()) \
    TND(QJsonDocument, JsonDocument, QJsonDocument()) \
    TND(QVariant, Variant, QVariant()) \
    TND(QImage, Image, QImage()) \


class VariableSetDocumentData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(VSDOCUMENT_DATAPROPS)
public:
    VariableSetDocumentData(void)
    {
        DEFINE_DATAPROPS_CTORS(VSDOCUMENT_DATAPROPS)
    }
};

class CORE_EXPORT VariableSetDocument : BaseDocumentObject
{
    DECLARE_PARENT_DATAPROPS(VSDOCUMENT_DATAPROPS)
    DECLARE_DATAPROPS(VariableSetDocument, VariableSetDocumentData)

public:
    VariableSetDocument(VariableSet * pVarSet);
    bool read(const QFileInfo & fi);
    bool write(const QFileInfo & fi);
    void close(void);
    bool parse(void);

private:
    VariableSet * mpVariableSet = nullptr;
    QDataStream * mpDataStream=nullptr;
    QTextStream * mpTextStream = nullptr;
};
