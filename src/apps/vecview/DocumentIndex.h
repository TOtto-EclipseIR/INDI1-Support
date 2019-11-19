#pragma once

#include <QObject>

#include <QList>
#include <QMap>

#include "../../libs/exe/BaseDocumentObject.h"

#include "VectorSetDocument.h"
#include "Vector.h"

class DocumentIndex : public QObject
{
    Q_OBJECT
public:
    explicit DocumentIndex(QObject * parent=nullptr);

public slots:

signals:

private:


};

