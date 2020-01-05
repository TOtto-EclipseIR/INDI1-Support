#include "HomePage.h"

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QTimer>

#include "Debug.h"

HomePage::HomePage(CentralStack * parent,
                     const int flags)
    : AbstractCentralPage(parent, flags)
{
    TRACEFN()
    setObjectName("HomePage");

    QTimer::singleShot(100, this, &HomePage::setupWidgets);
}

QString HomePage::pageName() const
{
    return QString("Home");
}

void HomePage::setupWidgets()
{
    TRACEFN()
    QPixmap splashPixmap(":/images/jpg/SplashPixmap");
    TRACE << splashPixmap.size();
    QLabel * splashLabel = new QLabel;
    splashLabel->setPixmap(splashPixmap);
    layout()->addWidget(splashLabel);
    show();
}
