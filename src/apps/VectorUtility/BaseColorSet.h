#pragma once

#include <QColor>
#include <QPair>
#include <QSettings>

typedef QPair<QColor, QColor> ForeBackGroundColors;


class BaseColorSet
{
public:
    BaseColorSet(void);
    void configureDefaults(void);
    void configure(const QSettings::SettingsMap & settings);
};

