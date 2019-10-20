#include "VVMainWindow.h"

#include <exe/BaseWidgetApp.h>

int main(int argc, char *argv[])
{
    BaseWidgetApp a(argc, argv);
    VVMainWindow w;
    w.show();
    return a.exec();
}
