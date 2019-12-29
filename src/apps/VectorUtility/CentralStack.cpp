#include "CentralStack.h"

#include "Debug.h"
#include "MainWindow.h"

CentralStack::CentralStack(MainWindow * parent)
    : QStackedWidget(parent)
    , mpMaster(parent->master())
{
    TRACEFN()
    setObjectName("CentralStack:VectorUtility");
    connect(this, &QStackedWidget::currentChanged,
            this, &CentralStack::indexChanged);



}

void CentralStack::setCurrentPage(const QString &name, const int sequence)
{
    QWidget * newPage = mPageMap.value(makeName(name, sequence));
    if (newPage) setCurrentWidget(newPage);
}

QWidget *CentralStack::createPage(const QString &name,
                                  const int sequence)
{
    TRACEFN()
    QSettings::SettingsMap pageSettings(master()->
            settings("{app}/{desktop}/{CentralStack}/pages/" + name));
    TRACE << pageSettings.keys();

}

QWidget *CentralStack::homePage(QSettings::SettingsMap pageSettings)
{

}

QString CentralStack::makeName(const QString &name,
                               const int sequence)
{
    QString fullName = name;
    if (sequence)
        fullName += QString("%1")
                .arg(sequence, 3, 10, QChar('0'));
    return fullName;
}

void CentralStack::indexChanged(int newIndex)
{
    // emit currentChanged()
}
