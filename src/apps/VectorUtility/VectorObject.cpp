#include "VectorObject.h"

#include <QDomDocument>
#include <QFileDialog>
#include <QImage>
#include <QTimer>

#include "Debug.h"

VectorObject::VectorObject(const Vector::FileScope scope,
                           QObject * parent)
    : QObject(parent)
    , cmScope(scope)
{
    setObjectName("VectorObject:"+Vector::scopeString(cmScope));
}

UnitFloat::Value VectorObject::at(const int x)
{
/*    return (x >= 0 && x < mCoefVector.size())
            ? UnitFloat::Value(coefVector().at(x))
            : UnitFloat(); */
    return coefVector().at(x);
}

void VectorObject::openFileName(const QString &fileName)
{
    TRACEFN()
    mFileInfo.setFile(fileName);
    if ("png" == mFileInfo.suffix().toLower())
            QTimer::singleShot(100, this,
                               &VectorObject::readPngFile);
    else if ("xml" == mFileInfo.suffix().toLower())
            QTimer::singleShot(100, this,
                               &VectorObject::readXmlFile);
    else
        emit openCancelled(cmScope);
}

void VectorObject::readPngFile(void)
{
    TRACEFN()
    QImage pngImage(mFileInfo.absoluteFilePath());
    TRACE << pngImage.textKeys();
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
    QFile xmlFile(mFileInfo.absoluteFilePath());
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
    TRACE << mCoefVector.at(0);
    emit opened(this);
}

void VectorObject::close(void)
{
    TRACEFN()
    TRACE << "Anything to do?";
    emit vectorClosed(cmScope);
}

