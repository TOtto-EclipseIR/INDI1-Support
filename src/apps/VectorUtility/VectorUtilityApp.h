#pragma once

#include <QObject>
#include <QApplication>

class VectorUtilityApp : public QApplication
{
    Q_OBJECT
public:
    explicit VectorUtilityApp(int ArgC, char * ArgV[]);

signals:

public slots:
};

