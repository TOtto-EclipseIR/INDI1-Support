#include "ActionManager.h"

#include "ApplicationSettings.h"
#include "BaseWidgetApp.h"

ActionManager::ActionManager(BaseWidgetApp * wgtApp)
    : QObject(wgtApp->object())
    , cmpWgtApp(wgtApp)
//    , cmpAppSettings(wgtApp->settings())
    , cmpSettings(new Settings(this))
{
    setObjectName("ActionManager");
    Settings::KeyValueList fileActions;
    Settings::KeyValueList helpActions;
    fileActions
            << Settings::KeyValuePair("OpenVectorFiles/Text",
                                      "&Open Vector Files")
            << Settings::KeyValuePair("Quit/Text", "&Quit")
               ;
    helpActions
            << Settings::KeyValuePair("AboutQt/Text",
                                      "About&Qt")
               ;
    cmpSettings->set("Actions/File", fileActions);
    cmpSettings->set("Actions/Help", helpActions);
}
