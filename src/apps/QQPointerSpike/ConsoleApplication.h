#pragma once

#include <QObject>
#include <QCoreApplication>

class ConsoleApplication : public QCoreApplication
{
public:
    ConsoleApplication(int argc, char *argv[]);
};
