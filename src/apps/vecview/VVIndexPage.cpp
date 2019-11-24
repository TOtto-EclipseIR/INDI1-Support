#include "VVIndexPage.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>

#include "base/Debug.h"

VVIndexPage::VVIndexPage(QWidget * parent)
    : QWidget(parent)
    , mpGrid(new QGridLayout(this))
{
    TRACEFN()
    setObjectName("VVIndexPage");
    QTimer::singleShot(100, this, SLOT(setupGrid()));
}

void VVIndexPage::setupGrid(void)
{
    QLabel * goLabel = new QLabel("Go");
    QLabel * baseLabel = new QLabel("Base");
    QLabel * subjectLabel = new QLabel("Subject");
    QLabel * titleLabel = new QLabel("Title");
    QLabel * infoLabel = new QLabel("Information");
    mpGrid->addWidget(goLabel, 0, 0);
    mpGrid->addWidget(baseLabel, 0, 1);
    mpGrid->addWidget(subjectLabel, 0, 2);
    mpGrid->addWidget(titleLabel, 0, 4);
    mpGrid->addWidget(infoLabel, 0, 5);
    emit gridSetup();
}
