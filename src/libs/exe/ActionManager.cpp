#include "ActionManager.h"

#include "ApplicationSettings.h"
#include "BaseWidgetApp.h"

ActionManager::ActionManager(BaseWidgetApp * wgtApp)
    : QObject(wgtApp->object())
    , cmpWgtApp(wgtApp)
    , cmpSettings(wgtApp->settings())
{

}
