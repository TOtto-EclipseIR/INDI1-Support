// file: VectorUtilityApp.h
#pragma once

#include <QObject>
#include <QApplication>

#include <QSettings>

#include <Debug.h>

#include "CentralStack.h"
#include "VectorItemModel.h"
#include "VectorObject.h"
#include "Version.h"
#include "VersionInfo.h"
class MainWindow;
class SearchResultObject;

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
    QString versionBuiltString(void) const;

public slots:
    void setVector(VectorObject * vector);
    void openVector(Vector::FileScope scope,
                    QString fileName);
    void openSearchResults(QDir dir);
    void matrixFileWritten(QString fileName);

protected slots:
    void startSetup(void);
    void setupMainWindow(void);
    void finishSetup(void);

signals:
    void ctorFinished(void);
    void setupFinished(void);
    void vectorOpened(VectorObject *);
    void vectorSet(VectorObject *);
    void scopeSet(Vector::FileScope);

private:
    MainWindow * mpMainWindow=nullptr;
    QSettings * mpSettings=nullptr;
    SearchResultObject * mpSearchResult=nullptr;
    int mCoefRows = 320;
    QHash<Vector::FileScope, VectorObject *> mVectorSet;
    const VersionInfo cmVersion;
};

