#pragma once
#include "Mdi.h"

#include <QMdiSubWindow>

class MDI_EXPORT BaseMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit BaseMdiSubWindow(QWidget * parent=nullptr);

signals:

public slots:
};

