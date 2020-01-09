#include "ConsoleApplication.h"

#include <QVector>

ConsoleApplication::ConsoleApplication(int argc, char *argv[])
    : QCoreApplication(argc, argv)
{
    QVector<int> iVec(10, 85);
    iVec[10] = 86;
}
