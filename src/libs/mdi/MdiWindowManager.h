#pragma once
#include "Mdi.h"

#include <QObject>

class MDI_EXPORT MdiWindowManager : public QObject
{
    Q_OBJECT
public:
    explicit MdiWindowManager(QObject * parent=nullptr);

public slots:

signals:

private:

};

