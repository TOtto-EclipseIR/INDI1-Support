// file: VectorUtilityApp.cpp

#include <QCoreApplication>
#include "VectorUtilityApp.h"

#include "VectorTableModel.h"


VectorUtilityApp::VectorUtilityApp(int ArgC, char *ArgV[])
    : QApplication(ArgC, ArgV)
    , mpTableModel(nullptr)
{
    setObjectName("VectorUtilityApp");
    setParent(qApp);
}
