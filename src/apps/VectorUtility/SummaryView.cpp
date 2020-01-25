#include "SummaryView.h"

#include <QFileInfo>
#include <QLabel>
#include <QTextEdit>
#include <QTimer>

#include "Debug.h"
#include "SummaryPage.h"
#include "VectorObject.h"

SummaryView::SummaryView(const Vector::FileScope scope,
                         QWidget * parent)
    : QWidget(parent)
    , cmScope(scope)
    , mpGridLayout(new QGridLayout)
    , mpFileNameText(new QTextEdit(parent))
    , mpDirNameText(new QTextEdit(parent))
    , mpFileSizeText(new QTextEdit(parent))
{
    TRACEQFI << Vector::scopeString(scope);
    setObjectName("SummaryView:"+Vector::scopeString(scope));
    TSTALLOC(mpFileNameText);
    QTimer::singleShot(100, this, &SummaryView::setupLayout);
}

void SummaryView::setupLayout()
{
    TRYALLOC(QLabel, FileNameLabel, QLabel);
    FileNameLabel->setText("File Name:");
    TRYALLOC(QLabel, DirectoryLabel, QLabel);
    DirectoryLabel->setText("Directory Name:");
    TRYALLOC(QLabel, FileSizeLabel, QLabel);
    FileSizeLabel->setText("File Size:");
    mpFileNameText->setReadOnly(true);
    mpGridLayout->addWidget(FileNameLabel,  0, 0);
    mpGridLayout->addWidget(DirectoryLabel, 1, 0);
    mpGridLayout->addWidget(FileSizeLabel,  2, 0);
    mpGridLayout->addWidget(mpFileNameText, 0, 1);
    mpGridLayout->addWidget(mpDirNameText, 1, 1);
    mpGridLayout->addWidget(mpFileSizeText, 2, 1);
    setLayout(mpGridLayout);
    emit layoutSetup(cmScope);
}

void SummaryView::setVector(VectorObject * vector)
{
    TRACEQFI << vector->scopeString();
    Vector::FileScope scope = vector->scope();
    EXPECTEQ(cmScope, scope);
    QFileInfo qfi = vector->data().getFileInfo();
    mpFileNameText->setPlainText(qfi.completeBaseName());
    mpDirNameText->setPlainText(qfi.dir().absolutePath());
    mpFileSizeText->setPlainText(QString::number(qfi.size()));
    update(); show();
}
