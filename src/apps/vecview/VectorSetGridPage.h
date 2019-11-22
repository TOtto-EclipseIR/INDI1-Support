#pragma once

#include <QWidget>

class VectorSetDocument;

class VectorSetGridPage : public QWidget
{
    Q_OBJECT
public:
    explicit VectorSetGridPage(VectorSetDocument * doc,
QWidget *parent = nullptr);

signals:

public slots:
};

