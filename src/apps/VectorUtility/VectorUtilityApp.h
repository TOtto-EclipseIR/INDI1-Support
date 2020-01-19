// file: VectorUtilityApp.h

#pragma once

#include <QObject>
#include <QApplication>


#include <QSettings>

#include "VectorItemModel.h"
#include "VectorObject.h"
#include "Version.h"
#include "VersionInfo.h"
class MainWindow;

class VectorUtilityApp : public QApplication
{
    Q_OBJECT
public:
    explicit VectorUtilityApp(int ArgC, char * ArgV[]);
    MainWindow * mainWindow(void);
    QSettings * settings(void);
    QSettings::SettingsMap settings(const QString & groupName);
    int rows(void) const
    { return mCoefRows; }
    VectorObject * vector(const Vector::FileScope scope);
    VersionInfo version(void) const
    { return cmVersion; }
    QString versionString(void) const;

public slots:
    void setMainWindow(MainWindow * mainWindow);
    void setVector(VectorObject * vector);
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }
    void openVector(Vector::FileScope scope,
                    QString fileName);

signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);
    void vectorOpened(VectorObject *);
    void vectorSet(VectorObject *);
    void scopeSet(Vector::FileScope);

private:
    MainWindow * mpMainWindow=nullptr;
    QSettings * mpSettings=nullptr;
    int mCoefRows = 320;
    QHash<Vector::FileScope, VectorObject *> mVectorSet;
    const VersionInfo cmVersion;
};

