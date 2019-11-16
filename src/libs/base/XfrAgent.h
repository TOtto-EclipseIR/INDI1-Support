// file: ./src/libs/base/XfrAgent.h
#pragma once
#include "Base.h"

#include <QObject>

class BASE_EXPORT XfrAgent : public QObject
{
    Q_OBJECT
public:
    explicit XfrAgent(QObject *parent = nullptr);

signals:

public slots:
};

