#pragma once

#include <QMdiArea>

class BaseMdiArea : public QMdiArea
{
    Q_OBJECT
public:
    explicit BaseMdiArea(QWidget *parent = nullptr);

signals:

public slots:
};

