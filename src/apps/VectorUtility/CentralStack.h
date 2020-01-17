#pragma once

#include <QWidget>
#include <QStackedWidget>

#include <QMap>
#include <QSettings>
#include <QString>
#include <QWidget>

#include "Debug.h"
#include "DualMap.h"
#include "Vector.h"
class AbstractCentralPage;
class MainWindow;
class VectorObject;
class VectorUtilityApp;

class CentralStack : public QStackedWidget
{
    Q_OBJECT
public:
    explicit CentralStack(MainWindow * parent=nullptr);
    VectorUtilityApp * master(void)
    { return CHKPTR(mpMaster); }
    QWidget * page(const QString & fullName);


public slots:
    void setCurrentView(const Vector::View & View);
    void setCurrentPage(const QString & fullName);
    void setVector(VectorObject * vector);

    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }


protected slots:
    void setupPages(void);
    void setupConnections(void);
    void scopeChanged(Vector::FileScope scope);
    void addCentralPage(AbstractCentralPage * newPage);
    void indexChanged(int newIndex);

signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

    void currentPageChanged(QString fullName, QWidget * page);
    void currentScopeChanged(Vector::FileScope);

private:
    VectorUtilityApp * mpMaster=nullptr;
    DualMap<QString, QWidget *> mFullNamePageDMap;
    AbstractCentralPage * mpHomePage=nullptr;
    AbstractCentralPage * mpCurrentPage=nullptr;
    Vector::FileScope mCurrentScope=Vector::nullScope;
};

