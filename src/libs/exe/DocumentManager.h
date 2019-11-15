// file: ./src/libs/exe/DocumentManager.h
#pragma once
#include "Exe.h"

#include <QObject>

#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QMap>
#include <QQueue>

#include "BaseDocumentObject.h"
#include "../../libs/indiBase/VectorSet/VectorSetDocument.h"

class EXE_EXPORT DocumentManager : public QObject
{
    Q_OBJECT
public:
    explicit DocumentManager(QObject * parent=nullptr);

public slots:
    void openAllFiles(QFileInfoList fil);
    void openNextFile(void);
//    void readFile(QFileInfo fi) {}
    void readFile(QFileInfo fi, BaseDocumentObject * doc);

signals:
    void fileRead(QFileInfo fi);

private:
    QFileInfoList mFileInfoSequentialList;
    QMap<QString, BaseDocumentObject *> mFileNameDocumentMap;
    QMap<QString, BaseDocumentObject *> mFileNameDocPendingMap;
    QQueue<QFileInfo> mWaitingFileInfoList;
};

