#include "DocumentManager.h"

#include <QTimer>


DocumentManager::DocumentManager(QObject * parent)
    : QObject(parent)
{
    setObjectName("DocumentManager");
    mFileInfoSequentialList.append(QFileInfo("{dummy[0]}"));
}

void DocumentManager::openAllFiles(QFileInfoList fil)
{
    mWaitingFileInfoList.append(fil);
    if (mWaitingFileInfoList.size())
        QTimer::singleShot(100, this, SLOT(openNextFile));
}

void DocumentManager::openNextFile(void)
{
    QFileInfo fi = mWaitingFileInfoList.takeFirst();
    BaseDocumentObject * doc=nullptr;

    if ("xml" == fi.suffix().toLower())
        doc = new BaseDocumentObject(
                    BaseDocumentObject::VectorSetXml,
                    mFileInfoSequentialList.size(), this);
    else if ("png" == fi.suffix().toLower())
        doc = new BaseDocumentObject(
                    BaseDocumentObject::VectorSetPng,
                    mFileInfoSequentialList.size(), this);
    else
        return;

    mFileInfoSequentialList.append(fi);
    mFileNameDocPendingMap.insert(fi.absoluteFilePath(), doc);

    if (mWaitingFileInfoList.size())
        QTimer::singleShot(100, this, SLOT(openNextFile));
}

void DocumentManager::readFile(QFileInfo fi,
                               BaseDocumentObject * doc)
{
    doc->readFile(fi);
}
