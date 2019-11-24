#include "BaseDocumentObject.h"

#include "../../libs/base/ErrorStatusObject.h"

int BaseDocumentObject::smSequence = 0;

BaseDocumentObject::BaseDocumentObject(DocumentClass docClass,
                                       QObject * parent)
    : QObject(parent)
    , mClass(docClass)
    , mpESO(new ErrorStatusObject(this))
{
    ++smSequence;
    setObjectName("BaseDocumentObject:"
                  +QString::number(smSequence));
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
    mQFI = fi;
    mpFile = new QFile(fi.filePath(), this);
    if ( ! mpFile->open(QIODevice::ReadOnly)) return false;
    mBytes = mpFile->readAll();
    emit fileRead(mQFI);
    return true;
}

QDomDocument BaseDocumentObject::parseDomDocument(void)
{
    QDomDocument doc;
    mpESO->tryDomSetContent(&doc, mBytes);
    return doc;
}

