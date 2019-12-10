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
#include "../base/ErrorStatusObject.h"

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
                                QObject * parent=nullptr);
    QString fileName(void) const
    { return mpFile ? mpFile->fileName() : QString(); }
    bool isError(void) const
    { return mpESO->isError(); }
    ErrorStatusObject * errorStatus(void) const
    { return mpESO; }

public slots:
    bool readFile(QFileInfo fi);
    virtual bool parse(void) { return false; }

signals:
    void fileRead(QFileInfo fi);
    void parsed(BaseDocumentObject * doc);

protected:
    QImage parseImage(QImage::Format format);
    QDomDocument parseDomDocument(void);

protected: // statics
    static int smSequence;
    
protected:
    QFileInfo mQFI;
    QFile * mpFile=nullptr;
    QByteArray mBytes;

private:
    DocumentClass mClass = nullDocumentClass;
    ErrorStatusObject * mpESO=nullptr;
};

