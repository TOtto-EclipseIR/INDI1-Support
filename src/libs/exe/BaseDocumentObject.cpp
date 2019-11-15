#include "BaseDocumentObject.h"

#include "../../libs/base/ErrorStatusObject.h"


BaseDocumentObject::BaseDocumentObject(DocumentClass docClass,
                                       const int sequence,
                                       QObject * parent)
    : QObject(parent)
    , mSequence(sequence)
    , mClass(docClass)
    , mpESO(new ErrorStatusObject(this))
{
        setObjectName("BaseDocumentObject");
}

bool BaseDocumentObject::isError(void) const
{
    return mpESO->isError();
}

ErrorStatusObject * BaseDocumentObject::errorStatus(void) const
{
    return mpESO;
}

bool BaseDocumentObject::readFile(QFileInfo fi)
{
    mFileInfo = fi;
    mpFile = new QFile(fi.filePath(), this);
    if ( ! mpFile->open(QIODevice::ReadOnly)) return false;
    mBytes = mpFile->readAll();
    emit fileRead(mFileInfo);
    return true;
}

QDomDocument BaseDocumentObject::parseDomDocument(void)
{
    QDomDocument doc;
    mpESO->tryDomSetContent(&doc, mBytes);
    return doc;
}

