#pragma once

#include <QMainWindow>
#include "VectorUtilityApp.h"

#include <QAction>
#include <QActionGroup>
#include <QHash>
#include <QMap>
#include <QMenu>
#include <QString>
#include <QVariant>

#include "Vector.h"
#include "VectorObject.h"
class VectorItemDelegate;
class VectorTableHorizontalHeader;
class VectorTableView;
class VectorTableVerticalHeader;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

public:
    MainWindow(VectorUtilityApp * parent);
    ~MainWindow();
    VectorUtilityApp * master(void)
    { return mpMaster; }

public slots:

protected slots:
    void setupMenuActions(void);
    void setupActionConnections(void);
    void openBaseline(void);
    void openSubjectOne(void);
    void openSubjectTwo(void);
    void openVectorDialog(Vector::FileScope scope);
    void closeAll(void);
    void close(const Vector::FileScope scope);
    void windowGroupTriggered(QAction * action);
    void viewGroupTriggered(QAction * action);

signals:
    void setupComplete(void);
    void openDialogCancelled(Vector::FileScope scope);
    void openDialogFileName(Vector::FileScope scope,
                             QString fileName);
    void closeScope(Vector::FileScope scope);
    void windowChanged(Vector::Window newWindow);
    void viewChanged(Vector::View newView);

private:
    QAction * menuAction(QMenu * menu,
                    const QString & menuText,
                    const QString & actionName,
                    const QVariant & actionData=QVariant(),
                    QActionGroup * actionGroup=nullptr);
    QAction * action(const QString & actionName) const;
    QList<QAction *> menuActions(QMenu * menu) const;

private:
    VectorUtilityApp * mpMaster=nullptr;
    VectorTableView * mpTableView=nullptr;
    VectorTableVerticalHeader * mpVerticalHeader=nullptr;
    VectorTableHorizontalHeader * mpHorizontalHeader=nullptr;
    VectorItemDelegate * mpItemDelegate=nullptr;
    QActionGroup * mpViewGroup=nullptr;
    QActionGroup * mpWindowGroup=nullptr;
    QHash<QString, QAction *> mNameActionMap;
    QMenu * mpFileMenu=nullptr;
    QMenu * mpViewMenu=nullptr;
    QMenu * mpWindowMenu=nullptr;
};
