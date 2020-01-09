// file: VectorUtilityApp.h

#pragma once

#include <QObject>
#include <QApplication>


#include <QSettings>

#include "VectorItemModel.h"
#include "VectorObject.h"
class MainWindow;
class VectorTableModel;

class VectorUtilityApp : public QApplication
{
    Q_OBJECT
public:
    explicit VectorUtilityApp(int ArgC, char * ArgV[]);
    MainWindow * mainWindow(void)
    { return mpMainWindow; }
    QSettings * settings(void)
    { return mpSettings; }
    QSettings::SettingsMap settings(const QString & groupName);
    VectorTableModel * tableModel(void)
    { return mpTableModel; }

public slots:
    void set(MainWindow * mainWindow);

    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }



signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);


private:
    VectorTableModel * mpTableModel=nullptr;
    MainWindow * mpMainWindow=nullptr;
    //VectorItemModel mItemModel;
    QSettings * mpSettings=nullptr;
    int mCoefRows = 320;
};

