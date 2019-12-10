#include "BaseDocumentObject.h"

#include "../base/Debug.h"
#include "../base/ErrorStatusObject.h"

int BaseDocumentObject::smSequence = 0;

BaseDocumentObject::BaseDocumentObject(DocumentClass docClass,
                                       QObject * parent)
    : QObject(parent)
    , mClass(docClass)
    , mpESO(new ErrorStatusObject(this))
{
    TRACEFN()

    ++smSequence;
    setObjectName("BaseDocumentObject:"
                  +QString::number(smSequence));
    connect(this, SIGNAL(fileRead(qfi)),
            this, SLOT(parse()));
}


bool BaseDocumentObject::readFile(QFileInfo fi)
{
    TRACEFN()
    mQFI = fi;
    mpFile = new QFile(fi.filePath(), this);
    if ( ! mpFile->open(QIODevice::ReadOnly)) return false;
    mBytes = mpFile->readAll();
    emit fileRead(mQFI);
    TRACE << "emit fileRead(mQFI)" << mQFI << mBytes.size();
    return true;
}

QDomDocument BaseDocumentObject::parseDomDocument(void)
{
    TRACEFN()
    QDomDocument doc;
    mpESO->tryDomSetContent(&doc, mBytes);
    TRACE << "return doc" << doc.documentElement().toElement().text();
    return doc;
}

