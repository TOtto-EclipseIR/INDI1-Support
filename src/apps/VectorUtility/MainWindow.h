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
    QList<QAction *> actionsFor(QMenu * menu) const;
    QAction * action(const QString & actionName) const;

public slots:
    void showMessage(const QString & status,
                     const int msecTime=0);
    void clearMessage(void);

public: // protected:
    void setVector(VectorObject * vector);

protected slots:
    void openBaseline(void);
    void openSubjectOne(void);
    void openSubjectTwo(void);
    void openVectorDialog(Vector::FileScope scope);
    void closeAll(void);
    void close(const Vector::FileScope scope);
    void viewGroupTriggered(QAction * action);

/***** MainWindow-Setup.cpp *****/
protected slots:
    void startSetup(void);
    void setupMenuActions(void);
    void setupStatus(void);
    void setupActionConnections(void);
    void finishSetup(void);

protected:
    QAction * addMenuAction(QMenu * menu,
                    const QString & menuText,
                    const QString & actionName,
                    const QVariant & actionData=QVariant(),
                    QActionGroup * actionGroup=nullptr);


signals:
    void ctorFinished(void);
    void setupFinished(void);

    void messageChanged(QString status);
    void openDialogCancelled(Vector::FileScope scope);
    void openDialogFileName(Vector::FileScope scope,
                             QString fileName);
    void closeScope(Vector::FileScope scope);
    void scopeChanged(Vector::FileScope newScope);
    void viewChanged(Vector::View newView);

private:
    VectorUtilityApp * mpMaster=nullptr;
    CentralStack * mpCentralStack=nullptr;

    QHash<QString, QAction *> mNameActionMap;
    QActionGroup * mpViewActionGroup=nullptr;
    QMenu * mpFileMenu=nullptr;
    QMenu * mpViewMenu=nullptr;
};
