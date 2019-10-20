#pragma once
#include "Exe.h"

#include <QApplication>

class EXE_EXPORT BaseWidgetApp : public QApplication
{
    Q_OBJECT
public:
    explicit BaseWidgetApp(int argc, char **argv);

signals:

public slots:
};

