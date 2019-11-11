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

class EXE_EXPORT DocumentManager : public QObject
{
    Q_OBJECT
public:
    explicit DocumentManager(QObject * parent=nullptr);

public slots:
    void openAllFiles(QFileInfoList fil) {}
    void readFile(QFileInfo fi) {}
    void fileRead(QFileInfo fi, BaseDocumentObject * doc) {}

signals:
    void fileRead(QFileInfo fi);

private:
    QFileInfoList mInfoSequentialList;
    QMap<QFileInfo, BaseDocumentObject *> mInfoDocumentMap;
    QMap<QFileInfo, BaseDocumentObject *> mInfoDocPendingMap;
    QQueue<QFileInfo> mWaitingFiles;
};

