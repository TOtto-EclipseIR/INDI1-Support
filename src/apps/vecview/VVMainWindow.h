#pragma once

#include <exe/BaseMainWindow.h>
class Settings;

class VVMainWindow : public BaseMainWindow
{
    Q_OBJECT
public:
    VVMainWindow(void);
    ~VVMainWindow();

public slots:
    void setupActions(void);

private:
    Settings * cmpSettings=nullptr;
};
