#pragma once

#include <QAction>

class BaseAction : public QAction
{
public:
    BaseAction(QObject * parent=nullptr);
};

