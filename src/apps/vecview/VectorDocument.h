#pragma once

#include "../../libs/mdi/BaseMdiDocument.h"

#include <QDomElement>

class VectorDocument : public BaseMdiDocument
{
    Q_OBJECT
public:
    explicit VectorDocument(MdiDocumentManager * parent=nullptr);

public slots:

signals:

private:
    QDomElement mRootElement;
};

