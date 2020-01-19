#include "VectorObject.h"

#include <QDomDocument>
#include <QFileDialog>
#include <QImage>
#include <QTimer>

#include "Debug.h"
#include "QObjectInfo.h"

QHash<Vector::FileScope, VectorObject *> VectorObject::mVectors;


VectorObject::VectorObject(const Vector::FileScope scope,
                           QObject * parent)
    : QObject(parent)
    , cmScope(scope)
    , mCoefVector(320)
{
    setObjectName("VectorObject:"+Vector::scopeString(cmScope));
    QObjectInfo qoi(this);
}

void VectorObject::set(VectorObject * vo)
{
    VectorObject * oldVector = mVectors[vo->scope()];
    if (oldVector) oldVector->deleteLater();
    mVectors[vo->scope()] = vo;

}


void VectorObject::openFileName(const QString & fileName)
{
    TRACEQFI << fileName;
    QFileInfo fileInfo;
    fileInfo.setFile(fileName);
    data().setFileInfo(fileInfo);
    if ("png" == fileInfo.suffix().toLower())
            QTimer::singleShot(100, this,
                               &VectorObject::readPngFile);
    else if ("xml" == fileInfo.suffix().toLower())
            QTimer::singleShot(100, this,
                               &VectorObject::readXmlFile);
    else
        emit openCancelled(cmScope);
}

void VectorObject::readPngFile(void)
{
    TRACEFN()
    QImage pngImage(data().getFileInfo().absoluteFilePath());
    TRACE << pngImage.textKeys();
    if (pngImage.height() > 16 && pngImage.width() > 16)
        data().setNormalizedImage(pngImage);
    QString xmlBytes = pngImage.text("INDIface").toLocal8Bit();
    data().setXmlString(xmlBytes);
//    TRACE << mXmlBytes;
    if ( ! xmlBytes.isEmpty())
        QTimer::singleShot(100, this, &VectorObject::getRootElement);
    else
        emit openCancelled(cmScope);
}

void VectorObject::readXmlFile(void)
{
    TRACEFN()
    QFile xmlFile(data().getFileInfo().absoluteFilePath());
    xmlFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString xmlBytes = xmlFile.readAll();
    data().setXmlString(xmlBytes);
    QTimer::singleShot(100, this, &VectorObject::getRootElement);
}

void VectorObject::getRootElement(void)
{
    TRACEFN()
    QDomDocument doc;
    doc.setContent(data().getXmlString());
    QDomElement rootElement = doc.documentElement();
    TRACE << rootElement.tagName();
    data().setRootElement(rootElement);
    if (rootElement.isElement())
        QTimer::singleShot(100, this,
                           &VectorObject::parseVectorElement);
    else
        emit openCancelled(cmScope);
}

void VectorObject::parseVectorElement(void)
{
    TRACEFN()
    QDomElement rootElement = data().getRootElement();
    QDomElement deVector;
    if ("INDIfaceFace" == rootElement.tagName())
    {
        QDomElement deSet = rootElement
                .firstChildElement("INDI-EigenFace-Template");
        //TRACE << deSet.text();
        deVector = deSet.firstChildElement(
                    "INDI-EigenFace-EigenFaceVector");
    }
    else
    {
        deVector = rootElement
                .firstChildElement("INDI-EigenFace-EigenFaceVector");
    }
    int count = deVector.attribute("Count").toInt();
    //TRACE << deVector.text();
    TRACE << count;
    mData.setCoefCount(count);
    mData.setCoefText(deVector.text());

    QTimer::singleShot(100, this, &VectorObject::setVectorCoefData);
}

void VectorObject::setVectorCoefData(void)
{
    TRACEFN()
    mCoefVector.setFromText(mData.getCoefText(),
                    mData.getCoefCount());
//    TRACE << mCoefVector.at(0);
    set(this);
    emit opened(this);
}

void VectorObject::close(void)
{
    TRACEQFI << "Anything to do?";
    emit vectorClosed(cmScope);
}

