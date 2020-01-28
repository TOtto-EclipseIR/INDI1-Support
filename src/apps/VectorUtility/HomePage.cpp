#include "HomePage.h"

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QTimer>

#include "Debug.h"

HomePage::HomePage(CentralStack * parent)
    : AbstractCentralPage(parent)
{
    TRACEFN()
    setObjectName("HomePage");
    connect(this, &HomePage::ctorFinished,
            this, &HomePage::startSetup);
    emit ctorFinished();
}

Vector::View HomePage::view() const
{
    return Vector::Home;
}

QString HomePage::pageName() const
{
    return QString("Home");
}


void HomePage::startSetup(void)
{
    TRACEFN()
    QTimer::singleShot(100, this, &HomePage::setupWidgets);
}

void HomePage::finishSetup()
{
    TRACEFN()
    emit setupFinished(view());
}

void HomePage::setupWidgets(void)
{
    TRACEFN()
    QPixmap splashPixmap(":/images/jpg/SplashPixmap");
    TRACE << splashPixmap.size();
    QLabel * splashLabel = new QLabel;
    QLabel * versionLabel = new QLabel;
    versionLabel->setText(stack()->app()->versionBuiltString());
    splashLabel->setPixmap(splashPixmap);
    layout()->addWidget(splashLabel, 1, 0, 5, 5, Qt::AlignCenter);
    layout()->addWidget(versionLabel, 0, 1, Qt::AlignCenter);
    show();
    finishSetup();
}
