#include "DocumentManager.h"

#include <QTimer>

#include "../base/Debug.h"

DocumentManager::DocumentManager(QObject * parent)
    : QObject(parent)
{
    TRACEFN()
    setObjectName("DocumentManager");
    mFileInfoSequentialList.append(QFileInfo("{dummy[0]}"));
}

void DocumentManager::openAllFiles(QFileInfoList fil)
{
    TRACEFN()
    mWaitingFileInfoList.append(fil);
    if ( ! mWaitingFileInfoList.empty())
        QTimer::singleShot(100, this, SLOT(openNextFile));
}

void DocumentManager::openNextFile(void)
{
    TRACEFN()
    if (mWaitingFileInfoList.isEmpty()) return;
    QFileInfo fi = mWaitingFileInfoList.takeFirst();
    BaseDocumentObject * doc=nullptr;

    if ("xml" == fi.suffix().toLower())
        doc = new BaseDocumentObject(
                    BaseDocumentObject::VectorSetXml,
                    this);
    else if ("png" == fi.suffix().toLower())
        doc = new BaseDocumentObject(
                    BaseDocumentObject::VectorSetPng,
                    this);
    else
        return;

    mFileInfoSequentialList.append(fi);
    mFileNameDocPendingMap.insert(fi.absoluteFilePath(), doc);

    if (mWaitingFileInfoList.size())
        QTimer::singleShot(100, this, SLOT(openNextFile()));
}

void DocumentManager::readFile(QFileInfo fi,
                               BaseDocumentObject * doc)
{
    TRACEFN()
    TRACE << fi << doc->objectName();
    doc->readFile(fi);
}
