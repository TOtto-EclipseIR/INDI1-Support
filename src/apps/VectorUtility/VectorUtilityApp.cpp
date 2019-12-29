// file: VectorUtilityApp.cpp

#include <QCoreApplication>
#include "VectorUtilityApp.h"

#include <QSettings>


#include "VectorTableModel.h"


VectorUtilityApp::VectorUtilityApp(int ArgC, char *ArgV[])
    : QApplication(ArgC, ArgV)
    , mpTableModel(nullptr)
    , mpSettings(new QSettings(this))
{
    setObjectName("VectorUtilityApp");
    setParent(qApp);
    mCoefRows = mpSettings->value("Vector/CoefRows",
                                  mCoefRows).toInt();
    /*
    VectorObject * baseVectorObject
            = new VectorObject(Vector::BaseLineFile);
    VectorObject * sub1VectorObject
            = new VectorObject(Vector::SubjectOneFile);
    VectorObject * sub2VectorObject
            = new VectorObject(Vector::SubjectTwoFile);
    set(baseVectorObject);
    set(sub1VectorObject);
    set(sub2VectorObject);
    connect(baseVectorObject, &VectorObject::opened,
            mpTableModel, &VectorTableModel::incomingVector);
  */
}

void VectorUtilityApp::set(VectorObject * vector)
{
    mScopeVectorMap.insert(vector->scope(), vector);
    connect(vector, &VectorObject::opened,
            mpTableModel, &VectorTableModel::appendVector);
}

void VectorUtilityApp::openVectorFile(Vector::FileScope scope,
                                      QString fileName)
{
    vector(scope)->openFileName(fileName);
}
