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

    QTimer::singleShot(100, this, &HomePage::setup0);
}

QString HomePage::pageName() const
{
    return QString("Home");
}

void HomePage::setup0()
{
    TRACEFN()
    QPixmap splashPixmap("/Temp/art/GradStack.jpg");
    TRACE << splashPixmap.size();
    QLabel * splashLabel = new QLabel;
    splashLabel->setPixmap(splashPixmap);
    layout()->addWidget(splashLabel);
    show();
    //    QTimer::singleShot(100, this, &HomePage::setup1);
}
