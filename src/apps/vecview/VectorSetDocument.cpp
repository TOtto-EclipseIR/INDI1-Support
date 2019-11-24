#include "VectorSetDocument.h"

#include <QLabel>
#include <QPixmap>
#include <QTextStream>

#include "../../libs/base/Debug.h"

#include "VectorSetWidget.h"

VectorSetDocument::VectorSetDocument(const QFileInfo qfi,
                                     QObject * parent)
    : BaseDocumentObject(VectorSetXml, parent)
    , mpVectorSetWidget(new VectorSetWidget(this))
{
    TRACEFN()
    setObjectName("VectorSetDocument:#"
                  + QString::number(smSequence));
    mQFI = qfi;
}

void VectorSetDocument::show(const QPixmap & pixmap)
{
    TRACEFN()
            widget()->label()->setPixmap(pixmap);
}

bool VectorSetDocument::parse(void)
{
    TRACEFN()
    QDomDocument doc = parseDomDocument();
    if ( isError() ) return false;  //----------

#if 0
    QDomNamedNodeMap docAttributes = doc.attributes();
    QDomNode statusAttributeNode
                = docAttributes.namedItem("Status");
    QDomText statusAttributeText = statusAttributeNode.toText();
    QString vectorSetStatus = QString();
#else
    QDomElement rootDE = doc.documentElement();
    QString vectorSetStatus = rootDE.attribute("Status");
#endif
    QDomElement idDE = rootDE.firstChildElement(cmIdTag);
    QDomElement vectorSetDE
                = rootDE.firstChildElement(cmVectorSetTag);
    QString faceId = idDE.attribute("FaceId");
    int faceKey = idDE.attribute("FaceKey").toInt();
    int personKey = idDE.attribute("PersonKey").toInt();
    QString personId = idDE.attribute("PersonId");
    int numVectors = idDE.attribute("Vectors").toInt();
    mVectorSetSet.set("Identification/VectorSetStatus", vectorSetStatus);
    mVectorSetSet.set("Identification/FaceId", faceId);
    mVectorSetSet.set("Identification/FaceKey", faceKey);
    mVectorSetSet.set("Identification/PersonKey", personKey);
    mVectorSetSet.set("Identification/PersonId", personId);
    mVectorSetSet.set("Identification/NumVectors", numVectors);

    int vectorIndex = 0;
    QDomElement vectorDE = vectorSetDE.firstChildElement(cmVectorTag);
    while (vectorIndex++ < numVectors && ! vectorDE.isNull())
    {
        vectorDE = vectorSetDE.nextSiblingElement();
        QString vectorId = vectorDE.attribute("VectorId");
        qreal residual = vectorDE.attribute("Residual").toDouble();
        int coefficientCount = vectorDE.attribute("Count").toInt();
        QString coefficientString = vectorDE.text();
        mVectorSetSet.set("VectorSet/"
                      +QString::number(vectorIndex)+"/Id",
                      vectorId);
        mVectorSetSet.set("VectorSet/"
                      +QString::number(vectorIndex)+"/Residual",
                      residual);
        mVectorSetSet.set("VectorSet/"
                          +QString::number(vectorIndex)
                          +"/CoefficientCount", coefficientCount);
        QVector<qreal> coefficientVector;
        coefficientVector.reserve(coefficientCount);
        QTextStream coefficientsStream(coefficientString.toLocal8Bit());
        int coefficientIndex = 0;
        qreal coefficientValue;
        while (coefficientIndex++ < coefficientCount
               && ! coefficientsStream.atEnd())
        {
            coefficientsStream >> coefficientValue;
            coefficientVector.append(coefficientValue);
            mVectorSetSet.set(coefficientIndex, coefficientValue);
        }
    }
    return true;
}
