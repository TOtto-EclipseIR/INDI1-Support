// file: VectorUtilityApp.h

#pragma once

#include <QObject>
#include <QApplication>

class VectorTableModel;

class VectorUtilityApp : public QApplication
{
    Q_OBJECT
public:
    explicit VectorUtilityApp(int ArgC, char * ArgV[]);

public slots:



signals:


private:
    VectorTableModel * mpTableModel=nullptr;
};

