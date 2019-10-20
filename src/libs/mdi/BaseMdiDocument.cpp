#include "BaseMdiDocument.h"

class MdiDocumentManager;

BaseMdiDocument::BaseMdiDocument(const QString & baseTitle,
                                 MdiDocumentManager * parent)
    : QObject((QObject *)(parent))
    , cmpManager(parent)
    , cmBaseTitle(baseTitle)
{
    setObjectName("BaseMdiDocument");
}
