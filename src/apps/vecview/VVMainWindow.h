#pragma once

#include <exe/BaseMainWindow.h>

#include <QFileInfo>
class Settings;

#include <core/VariableSet.h>
class ActionManager;
class DocumentActions;
class DocumentManager;


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
    void connections(void);
    bool readVectorSetFile(QFileInfo fi) {}

private:
    Settings * cmpSettings=nullptr;
    VariableSet mConfiguration;
    QMap<QString, QMenu *> mNameMenuMap;
    ActionManager * cmpActionManager=nullptr;
    DocumentActions * cmpDocumentActions=nullptr;
    DocumentManager * cmpDocumentManager=nullptr;
};
