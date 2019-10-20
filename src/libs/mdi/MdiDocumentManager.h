#pragma once
#include "Mdi.h"

#include <QObject>

class MDI_EXPORT MdiDocumentManager : public QObject
{
    Q_OBJECT
public:
    MdiDocumentManager(QObject * parent=nullptr);
};

