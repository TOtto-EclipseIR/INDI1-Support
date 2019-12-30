#include "CentralStack.h"

#include <QTimer>

#include "AbstractCentralPage.h"
#include "Debug.h"
#include "MainWindow.h"

#include "BlankPage.h"

CentralStack::CentralStack(MainWindow * parent)
    : QStackedWidget(parent)
    , mpMaster(parent->master())
{
    TRACEFN()
    setObjectName("CentralStack:VectorUtility");
    connect(this, &QStackedWidget::currentChanged,
            this, &CentralStack::indexChanged);


    QTimer::singleShot(100, this, &CentralStack::setupPages);
}

void CentralStack::setCurrentPage(const QString &fullName)
{
    QWidget * newPage = mFullNamePageDMap.at(fullName);
    if (newPage) setCurrentWidget(newPage);
}

void CentralStack::setupPages()
{
    //    addPage(new BlankPage(this, 0));
}

void CentralStack::addPage(AbstractCentralPage *newPage)
{
    // TODO TBD
}

/*
QWidget *CentralStack::createPage(const QString & baseName)
{
    TRACEFN()
    QSettings::SettingsMap pageSettings(master()->
            settings("{app}/{desktop}/{CentralStack}/pages/" + baseName));
    TRACE << pageSettings.keys();

}
*/

void CentralStack::indexChanged(int newIndex)
{
    QWidget * newPage = QStackedWidget::widget(newIndex);
    emit currentChanged(mFullNamePageDMap.at(newPage), newPage);
}
