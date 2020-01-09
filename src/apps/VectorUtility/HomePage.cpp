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
    connect(this, &HomePage::ctorFinished,
            this, &HomePage::startSetup);
    emit ctorFinished(this);
}

Vector::View HomePage::view() const
{
    return Vector::Home;
}

QString HomePage::pageName() const
{
    return QString("Home");
}


void HomePage::startSetup(QObject * thisObject)
{
    TRACEFN()
    Q_UNUSED(thisObject);
    QTimer::singleShot(100, this, &HomePage::setupWidgets);
}


void HomePage::setupWidgets(void)
{
    TRACEFN()
    QPixmap splashPixmap(":/images/jpg/SplashPixmap");
    TRACE << splashPixmap.size();
    QLabel * splashLabel = new QLabel;
    splashLabel->setPixmap(splashPixmap);
    layout()->addWidget(splashLabel);
    show();
    finishSetup(this);
}
