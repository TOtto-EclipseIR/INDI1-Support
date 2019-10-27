#include "AbstractMdiDocument.h"

AbstractMdiDocument::AbstractMdiDocument(MdiDocumentManager * parent)
    : QObject(parent)
    , cmpManager(parent)
{

}

void AbstractMdiDocument::open(QFileInfo fi,
                               QIODevice::OpenMode om)
{
    mFileInfo = fi;
    mOpenMode = om;
    mpFile = new QFile(fi.absoluteFilePath(), this);
    if (failed("Creating File", mpFile)) return;

    if (failed("Opening File", mpFile->open(mOpenMode))) return;
    emit opened(mpFile->openMode());
}

void AbstractMdiDocument::readAll(void)
{
    if (mpFile) mBytes = mpFile->readAll();
    if (failed("Reading File", ! mBytes.isEmpty())) return;
    emit allRead(mBytes.size());
}

void AbstractMdiDocument::setDomContent(void)
{
    if (failed("XmlDocumentSetContent",
               mDomDocument.setContent(mBytes, &mDomContentError,
                         &mDomContentRow, &mDomContentRow)))
        return;
    emit contentSet(mDomDocument.doctype().name());
    mRootElement = mDomDocument.documentElement();
    if (failed("IsElement", mRootElement.isElement()))
        return;
    emit rootExtracted(mRootElement.tagName());
}

void AbstractMdiDocument::close(void)
{
    mFileInfo = QFileInfo();
    mOpenMode = 0;
    if (mpFile) mpFile->close();
    mBytes.clear();
    mDomDocument.clear();
    mRootElement.clear();
}

bool AbstractMdiDocument::failed(QString op, const bool success)
{
    if (success) return false; // DON'T return in caller

    QVariantMap errorResult;
    errorResult.insert("Operation", op);
    if (nullptr != mpFile)
    {
        errorResult.insert("QFileErrorCode", mpFile->error());
        errorResult.insert("QFileError", mpFile->errorString());
        errorResult.insert("FileBytes", mBytes.size());
    }
    if (mDomContentError.isEmpty())
    {
        errorResult.insert("QDomDocError", mDomContentError);
        errorResult.insert("QDomDocRow", mDomContentRow);
        errorResult.insert("QDomDocCol", mDomContentCol);
    }
    emit fail(errorResult);
    close();
    return true; // DO return out of caller
}
