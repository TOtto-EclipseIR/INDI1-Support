#pragma once

#include <QWidget>
#include <QStackedWidget>

#include <QMap>
#include <QQueue>
#include <QSettings>
#include <QString>
#include <QWidget>

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
    typedef QQueue<Vector::View> ViewQueue;

public:
    explicit CentralStack(MainWindow * parent=nullptr);
    VectorUtilityApp * master(void);
    AbstractCentralPage * page(const Vector::View view);
    AbstractCentralPage * widget(int ix) const;

public slots:
    void setCurrentView(const Vector::View & View);
//    void setCurrentPage(const QString & pageName);
    void setVector(VectorObject * vector);

    void startSetup(void);
    void finishSetup(void)
    //    QMainWindow::setCentralWidget(mpCentralStack);
    { emit setupFinished(); }


protected slots:
    void setupNextPage(void);
    void addCentralPage(AbstractCentralPage * newPage);
    void indexChanged(int newIndex);

signals:
    void ctorFinished(void);
    void pageSetupStart(Vector::View view);
    void pageSetupFinished(Vector::View view);
    void setupFinished(void);
    void currentPageChanged(QString pageName, QWidget * page);

private:
    VectorUtilityApp * mpMaster=nullptr;
    ViewQueue mPendingSetupQueue;
    DualMap<Vector::View, AbstractCentralPage *> mViewPageDMap;
    AbstractCentralPage * mpHomePage=nullptr;
    AbstractCentralPage * mpCurrentPage=nullptr;
    Vector::FileScope mCurrentScope=Vector::nullScope;
};

