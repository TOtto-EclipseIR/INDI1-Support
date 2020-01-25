// file: VectorUtilityApp.cpp

#include <QCoreApplication>
#include "VectorUtilityApp.h"

#include <QSettings>
#include <QTimer>

#include "Debug.h"
#include "MainWindow.h"
#include "QObjectInfo.h"
#include "Version.h"
#include "VersionInfo.h"


VectorUtilityApp::VectorUtilityApp(int ArgC, char *ArgV[])
    : QApplication(ArgC, ArgV)
    , cmVersion(VER_STRING, VER_MAJOR, VER_MINOR,
                VER_RELEASE, VER_BRANCH, VER_BUILD)
{
    // This ctor runs in main(), before exec() starts event handling
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
    TSTALLOC(mpSettings)
    TRACE << mpSettings->fileName();
    mCoefRows = mpSettings->value("Vector/CoefRows",
                                  mCoefRows).toInt();
    EXPECT(connect(this, &VectorUtilityApp::ctorFinished,
            this, &VectorUtilityApp::startSetup));
    EXPECT(connect(this, &VectorUtilityApp::vectorOpened,
            this, &VectorUtilityApp::setVector));
    INFO << "Starting:" << arguments().first();
    INFO << cmVersion.toString() << "built" << cmVersion.buildDate();
    emit ctorFinished();
    TRACEQFI << "emit ctorFinished() -> startSetup() & exit" ;
}

MainWindow * VectorUtilityApp::mainWindow()
{
    return  CHKPTR(mpMainWindow);
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

QString VectorUtilityApp::versionBuiltString() const
{
    return QString("%1 %2").arg(cmVersion.toString())
                           .arg(cmVersion.buildDate());
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
    TODO("connect to vectorSet() signal; make protected in MainWindow")
    mainWindow()->setVector(vector);
}

void VectorUtilityApp::openVector(Vector::FileScope scope,
                                  QString fileName)
{
    TRACEQFI << Vector::scopeString(scope) << fileName;
    VectorObject * newVec = new VectorObject(scope, this);
    connect(newVec, &VectorObject::opened,
            this, &VectorUtilityApp::vectorOpened);
    newVec->openFileName(fileName);
    TRACEQFI << "exit";
}


void VectorUtilityApp::startSetup(void)
{
    TRACEFN()
    QTimer::singleShot(0, this, &VectorUtilityApp::setupMainWindow);
    TRACEQFI << "sshot setupMainWindow() exit";
}

void VectorUtilityApp::setupMainWindow(void)
{
    TRACEFN()
    mpMainWindow = new MainWindow(this);
    TSTALLOC(mpMainWindow);
    TRACE << mpMainWindow->objectName();
    EXPECT(connect(mpMainWindow, &MainWindow::openDialogFileName,
            this, &VectorUtilityApp::openVector));
    QTimer::singleShot(0, this, &VectorUtilityApp::finishSetup);
    TRACEQFI << "sshot finishSetup() exit";
}

void VectorUtilityApp::finishSetup(void)
{
    TRACEFN()
    emit setupFinished();
    TRACEQFI << "exit";
}


