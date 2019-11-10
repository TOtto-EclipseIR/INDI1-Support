#pragma once

#include <exe/BaseMainWindow.h>

#include <core/VariableSet.h>
class Settings;
class ActionManager;

class VVMainWindow : public BaseMainWindow
{
    Q_OBJECT
public:
    VVMainWindow(void);
    ~VVMainWindow();

public slots:
    void configure(void);
    void setupMenus(void);
    void setupActions(void);
    void fillMenus(void);

private:
    Settings * cmpSettings=nullptr;
    VariableSet mConfiguration;
    QMap<QString, QMenu *> mNameMenuMap;
    ActionManager * cmpActionManager=nullptr;
};
