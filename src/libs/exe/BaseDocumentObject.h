#ifndef BASEDOCUMENTOBJECT_H
#define BASEDOCUMENTOBJECT_H

#include <QObject>
#include "BaseDocument.h"
#include "DocumentManager.h"

#include <QFileInfo>
/*
class BaseDocumentObject : public QObject, BaseDocument
{
    Q_OBJECT
public:
    explicit BaseDocumentObject(DocumentManager * parent);
    QString baseTitle(void) const;
    QString newTitle(const int i);
    QString openTitle(const QFileInfo fi);
signals:

public slots:


protected:
    DocumentManager * cmpManager;
    QFileInfo mFileInfo;
    QFile * mpFile=nullptr;
    const QString cmBaseTitle;
    QString mTitle;


};
*/
#endif // BASEDOCUMENTOBJECT_H
