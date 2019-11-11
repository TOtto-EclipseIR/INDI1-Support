#pragma once

#include <QObject>


#include <QByteArray>
#include <QFile>
#include <QFileInfo>

class BaseDocumentObject : public QObject
{
    Q_OBJECT
public:
    explicit BaseDocumentObject(QObject * parent=nullptr);

public slots:
    bool readFile(QFileInfo fi) {}

signals:
    void fileRead(QFileInfo fi);

private:
    int mSequence=0;
    QFileInfo mFileInfo;
    QFile * mpFile=nullptr;
    QByteArray mBytes;


};

