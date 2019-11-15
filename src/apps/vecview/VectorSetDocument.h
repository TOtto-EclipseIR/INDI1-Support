// file: ./src/apps/vecview/VectorSetDocument.h
#pragma once

#include <QObject>


#include "../../libs/exe/BaseDocumentObject.h"
#include "../../libs/core/VariableMap.h"

class VectorSetDocument : public BaseDocumentObject
{
    Q_OBJECT
public:
    explicit VectorSetDocument(const DocumentClass docClass,
                               const int sequence,
                               QObject * parent=nullptr);

public slots:
    bool parse(void) override;

signals:

private:
    VariableMap mIdVectorSet;
    const QString cmRootTag = "INDIfaceFace";
    const QString cmIdTag = "Identification";
    const QString cmVectorSetTag = "INDI-EigenFace-Template";
    const QString cmVectorTag = "INDI-EigenFace-EigenFaceVector";
//    const QString cmRootTag = "INDIfaceFace";
};

