// file: VectorUtilityApp.cpp

#include <QCoreApplication>
#include "VectorUtilityApp.h"

#include <QSettings>
#include <QTimer>

#include "Debug.h"
#include "MainWindow.h"
#include "QObjectInfo.h"


VectorUtilityApp::VectorUtilityApp(int ArgC, char *ArgV[])
    : QApplication(ArgC, ArgV)
{
    TRACEFN()
    setParent(qApp);
    setObjectName("VectorUtilityApp");

#ifdef QT_DEBUG
    setOrganizationName("EclipseR&D");
#else
    setOrganizationName("EclipseIR");
#endif
    setApplicationName("VectorUtility");
    mpSettings = new QSettings(QSettings::UserScope, organizationName(),
                               applicationName(), this);
    //TRACE << mpSettings->fileName();
    mCoefRows = mpSettings->value("Vector/CoefRows",
                                  mCoefRows).toInt();
    connect(this, &VectorUtilityApp::ctorFinished,
            this, &VectorUtilityApp::startSetup);
    connect(this, &VectorUtilityApp::vectorOpened,
            this, &VectorUtilityApp::setVector);
    emit ctorFinished(this);
}

MainWindow * VectorUtilityApp::mainWindow()
{
    VCHKPTR(mpMainWindow);
    return mpMainWindow;
}

QSettings * VectorUtilityApp::settings()
{
    VCHKPTR(mpSettings);
    return mpSettings;
}

VectorObject * VectorUtilityApp::vector(const Vector::FileScope scope)
{
    TRACEQFI << Vector::scopeString(scope);
    VectorObject * scopeVector = mVectorSet.value(scope);
    return CHKPTR(scopeVector);
}

QSettings::SettingsMap VectorUtilityApp::
        settings(const QString & groupName)
{
    TRACE << Q_FUNC_INFO << groupName;
    QSettings::SettingsMap exportMap;
    mpSettings->beginGroup(groupName);
    QStringList keys = mpSettings->allKeys();
    foreach (QString key, keys)
        exportMap.insert(key, mpSettings->value(key));
    mpSettings->endGroup();
    return exportMap;
}

void VectorUtilityApp::setMainWindow(MainWindow * mainWindow)
{
    VCHKPTR(mainWindow);
    TRACEQFI << mainWindow->objectName();
    mpMainWindow = mainWindow;
    connect(mpMainWindow, &MainWindow::openDialogFileName,
            this, &VectorUtilityApp::openVector);
}


void VectorUtilityApp::setVector(VectorObject * vector)
{
    Vector::FileScope scope = vector->scope();
    TRACEQFI << Vector::scopeString(scope);
    if (mVectorSet.contains(scope))
    {
        VectorObject * oldVec = mVectorSet.value(scope);
        VCHKPTR(oldVec);
        oldVec->deleteLater();
    }
    VCHKPTR(vector);
    mVectorSet.insert(scope, vector);
    emit scopeSet(scope);
    emit vectorSet(vector);
    mainWindow()->setVector(vector);
}

void VectorUtilityApp::openVector(Vector::FileScope scope,
                                  QString fileName)
{
    VectorObject * newVec = new VectorObject(scope, this);
    connect(newVec, &VectorObject::opened,
            this, &VectorUtilityApp::vectorOpened);
    newVec->openFileName(fileName);
}


void VectorUtilityApp::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    finishSetup(this);
}
