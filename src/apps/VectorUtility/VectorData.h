#pragma once

#include <QSharedDataPointer>
#include "DataProperty.h"

#include <QByteArray>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QFileInfo>
#include <QImage>
#include <QPixmap>
#include <QString>
#include <QVariantHash>

//#include "UnitFloatLabel.h"
//#include "UnitFloatVector.h"
#include "Vector.h"

#define VECTORDATA_DATAPROPS(TND) \
    TND(int, ScopeInt, 0) \
    TND(QString, DialogCaption, QString()) \
    TND(QString, DialogFilter, QString()) \
    TND(QDir, DialogDir, QDir()) \
    TND(QFileInfo, FileInfo, QFileInfo()) \
    TND(QByteArray, FileBytes, QByteArray()) \
    TND(QImage, NormalizedImage, QImage()) \
    TND(QString, XmlString, QString()) \
    TND(QDomDocument, DomDocument, QDomDocument()) \
    TND(QDomElement, RootElement, QDomElement()) \
    TND(int, CoefCount, 0) \
    TND(QString, CoefText, QString()) \
    TND(QVariantHash, MetaPerson, QVariantHash()) \
    TND(QVariantHash, MetaFace, QVariantHash()) \
    TND(QVariantHash, MetaVector, QVariantHash()) \
    TND(QPixmap, GraphUnitPixmap, QPixmap()) \
    TND(QPixmap, ReconPixmap, QPixmap()) \
    TND(QPixmap, LEyePixmap, QPixmap()) \
    TND(QPixmap, REyePixmap, QPixmap()) \
    // TND(UnitFloatLabelVector, LabelVector, UnitFloatLabelVector())

class VectorDataData : public QSharedData
{
    DECLARE_CHILD_DATAPROPS(VECTORDATA_DATAPROPS)
public:
    VectorDataData(void)
    {
        DEFINE_DATAPROPS_CTORS(VECTORDATA_DATAPROPS)
    }
};

class VectorData
{
    DECLARE_PARENT_DATAPROPS(VECTORDATA_DATAPROPS)
    DECLARE_DATAPROPS(VectorData, VectorDataData)
public:
    Vector::FileScope scope(void) const
    { return  mScope; }
    QString scopeString(void) const
    { return Vector::scopeString(mScope); }
    QString title(void) const;

private:
    Vector::FileScope mScope=Vector::nullScope;

};
