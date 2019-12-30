#pragma once

#include <QWidget>
#include <QStackedWidget>

#include <QMap>
#include <QSettings>
#include <QString>
#include <QWidget>

#include "DualMap.h"
class AbstractCentralPage;
class MainWindow;
class VectorUtilityApp;

class CentralStack : public QStackedWidget
{
    Q_OBJECT
public:
    explicit CentralStack(MainWindow * parent=nullptr);
    VectorUtilityApp * master(void)
    { return mpMaster; }
    QWidget * page(const QString & fullName);


public slots:
    void setCurrentPage(const QString & fullName);

protected:
//    QWidget * createPage(const QString & baseName, const int sequence=0);

protected slots:
    void setupPages(void);

    void addPage(AbstractCentralPage * newPage);
    void indexChanged(int newIndex);

signals:
//    void pageCreated(QString fullName, QWidget * page);
    void currentChanged(QString fullName, QWidget * page);

private:
    VectorUtilityApp * mpMaster=nullptr;
    DualMap<QString, QWidget *> mFullNamePageDMap;
};

