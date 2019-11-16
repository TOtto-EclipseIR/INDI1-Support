// file: ./src/libs/base/XfrPublisher.h
#pragma once
#include "Base.h"

#include <QObject>

class BASE_EXPORT XfrPublisher : public QObject
{
    Q_OBJECT
public:
    explicit XfrPublisher(QObject *parent = nullptr);

signals:

public slots:
};

