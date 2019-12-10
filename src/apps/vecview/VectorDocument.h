#pragma once

#include <QObject>
#include "exe/BaseDocumentObject.h"

class VectorDocument : public BaseDocumentObject
{
    Q_OBJECT
public:
    explicit VectorDocument(BaseDocumentObject::DocumentClass docClass,
             BaseDocumentObject * parent=nullptr);

signals:

public slots:
};

