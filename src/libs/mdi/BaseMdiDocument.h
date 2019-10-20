#pragma once
#include "Mdi.h"

#include <QObject>

#include <QFile>
#include <QFileInfo>

//#include <exe/BaseDocument.h>
#include "../exe/BaseDocument.h"

class MdiDocumentManager;

class MDI_EXPORT BaseMdiDocument :public QObject
{
    Q_OBJECT
public:
    BaseMdiDocument(const QString & baseTitle,
                    MdiDocumentManager * parent=nullptr);
    QString baseTitle(void) const;
    QString newTitle(const int i);
    QString openTitle(const QFileInfo fi);

public slots:

protected:
    MdiDocumentManager * cmpManager;
    QFileInfo mFileInfo;
    QFile * mpFile=nullptr;
    const QString cmBaseTitle;
    QString mTitle;
};

