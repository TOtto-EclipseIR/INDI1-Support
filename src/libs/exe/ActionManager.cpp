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
}
