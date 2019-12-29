// file: VectorUtilityApp.h

#pragma once

#include <QObject>
#include <QApplication>
class QSettings;


#include "VectorObject.h"
class VectorTableModel;

class VectorUtilityApp : public QApplication
{
    Q_OBJECT
public:
    explicit VectorUtilityApp(int ArgC, char * ArgV[]);
    VectorObject * vector(const Vector::FileScope scope)
    { return mScopeVectorMap.value(scope); }

public slots:
    void set(VectorObject * vector);
    void openVectorFile(Vector::FileScope scope,
                        QString fileName);



signals:


private:
    VectorTableModel * mpTableModel=nullptr;
    QSettings * mpSettings=nullptr;
    int mCoefRows = 320;
    VectorObject::Map mScopeVectorMap;
};

