#pragma once

#include <QWidget>
#include <QStackedWidget>

#include <QMap>
#include <QSettings>
#include <QString>
#include <QWidget>

class MainWindow;
class VectorUtilityApp;

class CentralStack : public QStackedWidget
{
    Q_OBJECT
public:
    explicit CentralStack(MainWindow * parent=nullptr);
    VectorUtilityApp * master(void)
    { return mpMaster; }
    QWidget * page(const QString & name,
                   const int sequence=0);


public slots:
    void setCurrentPage(const QString & name,
                        const int sequence=0);


protected:
    QWidget * createPage(const QString & name,
                         const int sequence=0);
    QWidget * homePage(QSettings::SettingsMap pageSettings);
    QString makeName(const QString & name,
                     const int sequence);

protected slots:
    void indexChanged(int newIndex);


signals:
    void pageCreated(QString name, QWidget * page);
    void currentChanged(QString name, QWidget * page);



private:
    VectorUtilityApp * mpMaster=nullptr;
    QMap<QString, QWidget *> mPageMap;
};

