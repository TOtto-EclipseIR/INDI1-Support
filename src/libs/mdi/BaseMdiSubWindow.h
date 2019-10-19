#pragma once

#include <QMdiSubWindow>

class BaseMdiSubWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit BaseMdiSubWindow(QWidget * parent=nullptr);

signals:

public slots:
};

