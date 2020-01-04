// file: VectorUtilityApp.cpp

#include <QCoreApplication>
#include "VectorUtilityApp.h"

#include <QSettings>

#include "Debug.h"
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
    setOrganizationName("EclipseR&D");
    setApplicationName("VectorUtility");
    mpSettings = new QSettings(QSettings::UserScope, this);
    TRACE << mpSettings->fileName();
    mCoefRows = mpSettings->value("Vector/CoefRows",
                                  mCoefRows).toInt();
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

void VectorUtilityApp::openVectorFile(Vector::FileScope scope,
                                      QString fileName)
{
    vector(scope)->openFileName(fileName);
}
