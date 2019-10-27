#pragma once
#include "Exe.h"

#include <QApplication>

class ApplicationSettings;


class EXE_EXPORT BaseWidgetApp : public QApplication
{
    Q_OBJECT
public:
    explicit BaseWidgetApp(int argc, char **argv);
    QObject * object(void) { return qobject_cast<QObject *>(this); }
    ApplicationSettings * settings(void) { return cmpSettings; }

public slots:


signals:


private:
    ApplicationSettings * cmpSettings=nullptr;

};

