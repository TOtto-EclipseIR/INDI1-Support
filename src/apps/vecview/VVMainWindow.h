#pragma once

#include <exe/BaseMainWindow.h>

#include <QFileInfo>
class QTabWidget;

#include <core/VariableSet.h>
class ActionManager;
class Settings;
class DocumentActions;
class DocumentManager;

class VVHomeStack;
class VVHomeCoverPage;
class VVIndexPage;


class VVMainWindow : public BaseMainWindow
{
    Q_OBJECT
public:
    VVMainWindow(void);

public slots:
    void configure(void);
    void setupWindows(void);
    void setupActions(void);
    void setupMenus(void);
    void makeConnections(void);

private:
    Settings * mpSettings=nullptr;
    QTabWidget * mpMainTabWidget=nullptr;
    VVHomeStack * mpHomeStack=nullptr;
    VVHomeCoverPage * mpHomePage=nullptr;
    VVIndexPage * mpmpIndexPage;
    ActionManager * mpActionManager=nullptr;
    DocumentActions * mpDocumentActions=nullptr;
    DocumentManager * mpDocumentManager=nullptr;
    VariableSet mConfiguration;
    QMap<QString, QMenu *> mNameMenuMap;
};
