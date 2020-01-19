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
    setNames();
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
    QLabel * versionLabel = new QLabel;
    versionLabel->setText(stack()->master()->versionString());
    splashLabel->setPixmap(splashPixmap);
    layout()->addWidget(splashLabel, 1, 0, 5, 5, Qt::AlignCenter);
    layout()->addWidget(versionLabel, 0, 1, Qt::AlignCenter);
    show();
    finishSetup(this);
}
