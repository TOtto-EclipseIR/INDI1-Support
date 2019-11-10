#pragma once

#include <exe/BaseMainWindow.h>

#include <core/VariableSet.h>
class Settings;

class VVMainWindow : public BaseMainWindow
{
    Q_OBJECT
public:
    VVMainWindow(void);
    ~VVMainWindow();

public slots:
    void configure(void);
    void setupActions(void);

private:
    Settings * cmpSettings=nullptr;
    VariableSet mConfiguration;
};
