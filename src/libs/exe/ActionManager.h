#pragma once

#include <QObject>

#include<QString>
class QAction;
class QMenu;

#include "../core/VariableSet.h"

typedef QMap<QString, QMenu *> NameMenuMap;
typedef QMap<QString, QAction *> NameActionMap;

class ActionManager : public QObject
{
    Q_OBJECT
public:
    explicit ActionManager(QObject * parent=nullptr);
    void configure(const VariableSet & config,
                   NameMenuMap * nameMenus=nullptr);

public slots:


signals:

private:
    NameActionMap mNameActionMap;
};

