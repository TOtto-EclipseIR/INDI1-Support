// file: VectorUtilityApp.h

#pragma once

#include <QObject>
#include <QApplication>


#include <QSettings>

#include "VectorItemModel.h"
#include "VectorObject.h"
class MainWindow;
class VectorTableModel;

class VectorUtilityApp : public QApplication
{
    Q_OBJECT
public:
    explicit VectorUtilityApp(int ArgC, char * ArgV[]);
    MainWindow * mainWindow(void)
    { return mpMainWindow; }
    QSettings * settings(void)
    { return mpSettings; }
    QSettings::SettingsMap settings(const QString & groupName);
    VectorObject * vector(const Vector::FileScope scope)
    { return mScopeVectorMap.value(scope); }
    VectorTableModel * tableModel(void)
    { return mpTableModel; }

public slots:
    void set(VectorObject * vector);
    void set(MainWindow * mainWindow);
    void openVectorFile(Vector::FileScope scope,
                        QString fileName);

protected slots:
    void setupConnections(void);



signals:


private:
    VectorTableModel * mpTableModel=nullptr;
    MainWindow * mpMainWindow=nullptr;
    VectorItemModel mItemModel;
    QSettings * mpSettings=nullptr;
    int mCoefRows = 320;
    VectorObject::Map mScopeVectorMap;
};

