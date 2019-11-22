// file: ./src/libs/exe/BaseDocumentObject.h
#pragma once
#include "Exe.h"

#include <QObject>


#include <QByteArray>
#include <QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QMap>

#include "../core/VariableSet.h"
class ErrorStatusObject;

class EXE_EXPORT BaseDocumentObject : public QObject
{
    Q_OBJECT
public:
    enum DocumentClass
    {
        nullDocumentClass = 0,
        VectorSetXml,
        VectorSetPng,

        sizeDocumentClass
    };

public:
    explicit BaseDocumentObject(const DocumentClass docClass,
                                const int sequence,
                                QObject * parent=nullptr);
    bool isError(void) const;
    ErrorStatusObject * errorStatus(void) const;

public slots:
    bool readFile(QFileInfo fi);
    virtual bool parse(void) { return false; }

signals:
    void fileRead(QFileInfo fi);
    void parsed(BaseDocumentObject * doc);

protected:
    QImage parseImage(QImage::Format format);
    QDomDocument parseDomDocument(void);
    
protected:
    QFileInfo mFileInfo;
    QFile * mpFile=nullptr;
    QByteArray mBytes;

private:
    int mSequence=0; // TODO: fix sequence number handling
    DocumentClass mClass = nullDocumentClass;
    ErrorStatusObject * mpESO=nullptr;
};

