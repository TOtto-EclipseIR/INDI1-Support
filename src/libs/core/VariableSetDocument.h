#pragma once
#include "Core.h"

#include <QSharedDataPointer>
#include "../base/DataProperty.h"

#include <QBuffer>
#include <QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QJsonDocument>

#include "VariableSet.h"

#define VSDOCUMENT_DATAPROPS(TND) \
    TND(QDomDocument, DomDocument, QDomDocument()) \
    TND(QJsonDocument, JsonDocument, QJsonDocument()) \
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

class CORE_EXPORT VariableSetDocument
{
    DECLARE_PARENT_DATAPROPS(VSDOCUMENT_DATAPROPS)
    DECLARE_DATAPROPS(VariableSetDocument, VariableSetDocumentData)
};
