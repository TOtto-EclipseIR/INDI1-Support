#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <QObject>

#include <QMap>
#include <QMenu>
#include <QString>
#include <QVariant>

#include "../core/BasicId.h"
#include "../core/BasicName.h"

#include "BaseAction.h"
#include "Settings.h"
//class ApplicationSettings;
class BaseWidgetApp;

class ActionManager : public QObject
{
    Q_OBJECT
public:
    typedef BasicId ActionId;

public:
    explicit ActionManager(BaseWidgetApp * wgtApp);
    QMenu * menu(const BasicId & name)
    { return mNameMenuMap.value(name); }
    BaseAction * create(const ActionId id,
                        const QVariantMap config);

public slots:
    void registerMenu(const BasicName & name, QMenu * menu)
    { mNameMenuMap.insert(name, menu); }
    void setup(Settings::KeyValueList & kvs) {}
    void setup(ActionId settingsGroup) {;} // TODO
    void connect(ActionId id, QObject * object) {;}
    void activate(void) {;}
    void activate(bool checked) {;}

signals:
    void settingsFor(ActionId);
    void settingsComplete(void);
    void connected(QString objName);
    void activation(ActionId);
    void activateOk(ActionId, QVariantMap); // TODO ActionUid??
    void activateCancel(ActionId);
    void activateFail(ActionId, QVariantMap reason);

private:
    BaseWidgetApp * cmpWgtApp=nullptr;
//    ApplicationSettings * cmpAppSettings=nullptr;
    Settings * cmpSettings=nullptr;
    QMap<BasicName, QMenu *> mNameMenuMap;
    QMap<ActionId, BaseAction *> mIdActionMap;
};

#endif // ACTIONMANAGER_H
