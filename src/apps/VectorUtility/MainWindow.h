#pragma once

#include <QMainWindow>
#include "VectorUtilityApp.h"

#include <QAction>
#include <QActionGroup>
#include <QHash>
#include <QMap>
#include <QMenu>
#include <QStackedWidget>
#include <QString>
#include <QVariant>

#include "Vector.h"
#include "VectorObject.h"
class CentralStack;
class VectorItemDelegate;
class VectorTableHorizontalHeader;
class VectorTableView;
class VectorTableVerticalHeader;
class VectorTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

public:
    MainWindow(VectorUtilityApp * parent);
    ~MainWindow();
    VectorUtilityApp * master(void);
    CentralStack * stack(void);
    QMenu * scopeMenu(void)
    { return mpScopeMenu; }
    QAction * action(const QString & actionName) const;
    QList<QAction *> menuActions(QMenu * menu) const;

public slots:
    void showMessage(const QString & status,
                     const int msecTime=0);
    void clearMessage(void);
//  TODO setStatusLabel(), startStatusProgress(), enableCancel()
//  TODO mainToolBar
    void setVector(VectorObject * vector);

protected slots:
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }
    void setupMenuActions(void);
    void setupStatus(void);
    void setupActionConnections(void);
    void openBaseline(void);
    void openSubjectOne(void);
    void openSubjectTwo(void);
    void openVectorDialog(Vector::FileScope scope);
    void closeAll(void);
    void close(const Vector::FileScope scope);
    void scopeGroupTriggered(QAction * action);
    void viewGroupTriggered(QAction * action);
    void setScopeCheck(Vector::FileScope scope);

signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

    void messageChanged(QString status);
    void openDialogCancelled(Vector::FileScope scope);
    void openDialogFileName(Vector::FileScope scope,
                             QString fileName);
    void closeScope(Vector::FileScope scope);
    void scopeChanged(Vector::FileScope newScope);
    void viewChanged(Vector::View newView);


private:
    QAction * menuAction(QMenu * menu,
                    const QString & menuText,
                    const QString & actionName,
                    const QVariant & actionData=QVariant(),
                    QActionGroup * actionGroup=nullptr);

private:
    VectorUtilityApp * mpMaster=nullptr;
    CentralStack * mpCentralStack=nullptr;

    QHash<QString, QAction *> mNameActionMap;
    QActionGroup * mpViewActionGroup=nullptr;
    QActionGroup * mpScopeActionGroup=nullptr;
    QMenu * mpFileMenu=nullptr;
    QMenu * mpViewMenu=nullptr;
    QMenu * mpScopeMenu=nullptr;
};
