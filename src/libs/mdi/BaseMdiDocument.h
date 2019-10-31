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

public slots:

protected:
};

