#pragma once

#include <QObject>

#include <QByteArray>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QVariantMap>

#include "MdiDocumentManager.h"

class AbstractMdiDocument : public QObject
{
    Q_OBJECT
public:
    typedef QString FileSysExtName; // TODO FileSys Types
    typedef QString FileExtName;
    typedef QString FileExtId;
    typedef QString FileExtDesc;
    typedef QList<FileSysExtName> FileSysExtList;

public:
    explicit AbstractMdiDocument(MdiDocumentManager * parent);

protected:
    static void registerExtensions(const FileSysExtList extList,
                    const FileExtId extId,
                    const FileExtName extName=FileExtName(),
                    const FileExtDesc extDesc=FileExtDesc());

public slots:
    void open(QFileInfo fi, QIODevice::OpenMode om);
    void readAll(void);
    void setDomContent(void);
    virtual void close(void);
    virtual void process(QVariantMap config, QVariantMap input) = 0;

signals:
    void opened(QIODevice::OpenMode);
    void allRead(int bytes);
    void contentSet(QString docType);
    void rootExtracted(QString tagName);
    void processed(QVariantMap result);
    void closed(void);
    void fail(QVariantMap reason);
    void processFail(QVariantMap);

private:
    bool failed(QString op, const bool success);
    bool handleQFileError(bool success);
    bool doDomDocContent(void);

private:
    MdiDocumentManager * cmpManager=nullptr;
    QFileInfo mFileInfo;
    QIODevice::OpenMode mOpenMode;
    QFile * mpFile=nullptr;
    QByteArray mBytes;
    QDomDocument mDomDocument;
    QDomElement mRootElement;
    QString mDomContentError;
    int mDomContentRow = 0;
    int mDomContentCol = 0;
    QVariantMap mDocData;

    static QMap<FileSysExtName, FileExtId> smFileExtId;
    static QMap<FileExtId, FileExtName> smIdNameMap;
    static QMap<FileExtId, FileExtDesc> smIdDescMap;
};
