#include "VectorUtilityApp.h"
#include "MainWindow.h"


int main(int argc, char *argv[])
{
    VectorUtilityApp a(argc, argv);
    MainWindow w(&a);
    w.show();
    return a.exec();
}
