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
    , mpTableModel(new VectorTableModel())
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

    QTimer::singleShot(1000, this, &VectorUtilityApp::setupConnections);
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

void VectorUtilityApp::set(VectorObject * vector)
{
    mScopeVectorMap.insert(vector->scope(), vector);
    connect(vector, &VectorObject::opened,
            mpTableModel, &VectorTableModel::appendVector);
    mItemModel.set(vector);
}

void VectorUtilityApp::set(MainWindow *mainWindow)
{
    mpMainWindow = mainWindow;
}

void VectorUtilityApp::openVectorFile(Vector::FileScope scope,
                                      QString fileName)
{
    VectorObject * vec = vector(scope);
    if ( ! vec)
    {
        vec = new VectorObject(scope, this);
        set(vec);
    }
    vec->openFileName(fileName);
}

void VectorUtilityApp::setupConnections()
{
    TRACEFN()
    VectorObject * vo = new VectorObject(Vector::BaseLine);
    QObjectInfo qoi(vo);
    TRACE << qoi.enumNames();
}
