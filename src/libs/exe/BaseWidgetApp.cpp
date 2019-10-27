#include "BaseWidgetApp.h"

#include "ApplicationSettings.h"

BaseWidgetApp::BaseWidgetApp(int argc, char **argv)
    : QApplication(argc, argv)
    , cmpSettings(new ApplicationSettings(object()))
{

}
