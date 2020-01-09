// file: VectorUtilityApp.cpp

#include <QCoreApplication>
#include "VectorUtilityApp.h"

#include <QSettings>
#include <QTimer>

#include "Debug.h"
#include "MainWindow.h"
#include "QObjectInfo.h"
#include "VectorTableModel.h"


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
    TRACE << mpSettings->fileName();
    mCoefRows = mpSettings->value("Vector/CoefRows",
                                  mCoefRows).toInt();

    mpTableModel = new VectorTableModel(mCoefRows, this);

    connect(this, &VectorUtilityApp::ctorFinished,
            this, &VectorUtilityApp::startSetup);
    connect(this, &VectorUtilityApp::ctorFinished,
            mpTableModel, &VectorTableModel::startSetup);

    emit ctorFinished(this);
}

QSettings::SettingsMap VectorUtilityApp::
        settings(const QString & groupName)
{
    TRACE << Q_FUNC_INFO << mpSettings->fileName();
    QSettings::SettingsMap snapshot;
    mpSettings->beginGroup(groupName);
    QStringList keys = mpSettings->allKeys();
    foreach (QString key, keys)
        snapshot.insert(key, mpSettings->value(key));
    mpSettings->endGroup();
    return  snapshot;
}

void VectorUtilityApp::set(MainWindow * mainWindow)
{
    mpMainWindow = mainWindow;
}



void VectorUtilityApp::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    finishSetup(this);
}
