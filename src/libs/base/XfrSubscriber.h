// file: ./src/libs/base/XfrSubscriber.h
#pragma once
#include "Base.h"

#include <QObject>

class BASE_EXPORT XfrSubscriber : public QObject
{
    Q_OBJECT
public:
    explicit XfrSubscriber(QObject *parent = nullptr);

signals:

public slots:
};

