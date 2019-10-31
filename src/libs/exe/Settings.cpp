#include "Settings.h"

Settings::Settings(QObject * parent)
    : QSettings(parent)
{
    setObjectName("Settings");
}
