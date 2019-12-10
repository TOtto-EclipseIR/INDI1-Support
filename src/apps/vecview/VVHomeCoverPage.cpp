#include "VVHomeCoverPage.h"

#include <QByteArray>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QGridLayout>
#include <QImage>
#include <QSizePolicy>
#include <QTimer>

#include "base/Debug.h"

VVHomeCoverPage::VVHomeCoverPage(QWidget * parent)
    : QWidget(parent)
{
    TRACEFN()
    setObjectName("VVHomeCoverPage");
#if 0
    QFileInfo qfi("GradStack.jpg");
    TRACE << qfi.exists() << qfi.absoluteFilePath() << qfi;
    QFile * file = new QFile(qfi.filePath());
    file->open(QIODevice::ReadOnly);
    QByteArray qba = file->readAll();
    QImage pxmImage = QImage::fromData(qba);
    mPixmap = QPixmap::fromImage(pxmImage);
    TRACE << qba.size() << pxmImage.size() << mPixmap.size();
//    mPixmap = QPixmap("GradStack.jpg");
    mLabel.setPixmap(mPixmap);
//    mLabel.setSizePolicy(QSizePolicy::Minimum);
    mLabel.setMinimumSize(mPixmap.size());
    QGridLayout HomeCoverLayout;
    HomeCoverLayout.addWidget(&mLabel, 0 ,0);
    setLayout(&HomeCoverLayout);
#endif
    QTimer::singleShot(100, this, SLOT(setup()));
}

void VVHomeCoverPage::setup()
{
    TRACEFN()
#if 1
    QImage pixmapImage("GradStack.jpg");
    pixmapImage.scaledToWidth(640);
//    mPixmap = QPixmap("GradStack.jpg");
    mPixmap = QPixmap::fromImage(pixmapImage);
    mLabel.setPixmap(mPixmap);
//    mLabel.setSizePolicy(QSizePolicy::Minimum);
    mLabel.setMinimumSize(mPixmap.size());
    QGridLayout HomeCoverLayout;
    HomeCoverLayout.addWidget(&mLabel, 0 ,0);
    setLayout(&HomeCoverLayout);
#endif
    emit setup( ! mPixmap.isNull());
}
