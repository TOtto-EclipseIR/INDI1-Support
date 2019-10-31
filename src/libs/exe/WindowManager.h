#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>

class WindowManager : public QObject
{
    Q_OBJECT
public:
    explicit WindowManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // WINDOWMANAGER_H
