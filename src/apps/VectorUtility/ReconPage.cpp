#include "ReconPage.h"

#include <QTimer>

#include "Debug.h"


ReconPage::ReconPage(CentralStack * parent)
    : AbstractCentralPage(parent)
    , mpBaselineReconPixmapLabel(new QLabel)
    , mpSubjectOneReconPixmapLabel(new QLabel)
    , mpSubjectTwoReconPixmapLabel(new QLabel)
    , mpBaselineNormalPixmapLabel(new QLabel)
    , mpSubjectOneNormalPixmapLabel(new QLabel)
    , mpSubjectTwoNormalPixmapLabel(new QLabel)
{
    TRACEFN()
    setObjectName("ReconPage");
    connect(this, &ReconPage::ctorFinished,
            this, &ReconPage::startSetup);
    emit ctorFinished();
//    QTimer::singleShot(100, this, &ReconPage::setup0);
}

Vector::View ReconPage::view() const
{
    return Vector::Reconstruction;
}

QString ReconPage::pageName() const
{
    return "Reconstruction";
}

void ReconPage::startSetup(void)
{
    TRACEFN()

    mBaselineReconPixmap = QPixmap(cmSize);
    mSubjectOneReconPixmap = QPixmap(cmSize);
    mSubjectTwoReconPixmap = QPixmap(cmSize);
    mBaselineNormalPixmap = QPixmap(cmSize);
    mSubjectOneNormalPixmap = QPixmap(cmSize);
    mSubjectTwoNormalPixmap = QPixmap(cmSize);

    QLabel * baselineTextLabel = new QLabel("Baseline");
    QLabel * subjectOneTextLabel = new QLabel("SubjectOne");
    QLabel * subjectTwoTextLabel = new QLabel("SubjectTwo");
    TSTALLOC(baselineTextLabel)
    TSTALLOC(subjectOneTextLabel)
    TSTALLOC(subjectTwoTextLabel)
    layout()->addWidget(baselineTextLabel, 1, 0, Qt::AlignTop | Qt::AlignRight);
    layout()->addWidget(subjectOneTextLabel, 2, 0, Qt::AlignTop | Qt::AlignRight);
    layout()->addWidget(subjectTwoTextLabel, 3, 0, Qt::AlignTop | Qt::AlignRight);

    mpBaselineReconPixmapLabel->setPixmap(mBaselineReconPixmap);
    mpSubjectOneReconPixmapLabel->setPixmap(mSubjectOneReconPixmap);
    mpSubjectTwoReconPixmapLabel->setPixmap(mSubjectTwoReconPixmap);
    mpBaselineNormalPixmapLabel->setPixmap(mBaselineNormalPixmap);
    mpSubjectOneNormalPixmapLabel->setPixmap(mSubjectOneNormalPixmap);
    mpSubjectTwoNormalPixmapLabel->setPixmap(mSubjectTwoNormalPixmap);

    layout()->addWidget(mpBaselineReconPixmapLabel, 1, 1, Qt::AlignCenter);
    layout()->addWidget(mpSubjectOneReconPixmapLabel, 2, 1, Qt::AlignCenter);
    layout()->addWidget(mpSubjectTwoReconPixmapLabel, 3, 1, Qt::AlignCenter);
    layout()->addWidget(mpBaselineNormalPixmapLabel, 1, 2, Qt::AlignCenter);
    layout()->addWidget(mpSubjectOneNormalPixmapLabel, 2, 2, Qt::AlignCenter);
    layout()->addWidget(mpSubjectTwoNormalPixmapLabel, 3, 2, Qt::AlignCenter);

    setLayout(layout());
//    update();
  //  updateGeometry();
    show();
    TRACEQFI << "exit";
}

void ReconPage::setVector(VectorObject * vector)
{
    AbstractCentralPage::setVector(vector);
    Vector::FileScope scope = vector->scope();
    QImage normal = vector->data().getNormalizedImage();
    if (normal.isNull())
        clearNormal(scope);
    else
        setNormal(scope, normal);
}

void ReconPage::clearNormal(const Vector::FileScope scope)
{
    TRACEQFI << Vector::scopeString(scope);
    switch (scope)
    {
    case Vector::Baseline:
        mBaselineNormalPixmap = QPixmap(cmSize);
        mpBaselineNormalPixmapLabel->setPixmap(mBaselineNormalPixmap);
        break;

    case Vector::SubjectOne:
        mSubjectOneNormalPixmap = QPixmap(cmSize);
        mpSubjectOneNormalPixmapLabel->setPixmap(mSubjectOneNormalPixmap);
        break;

    case Vector::SubjectTwo:
        mSubjectTwoNormalPixmap = QPixmap(cmSize);
        mpSubjectTwoNormalPixmapLabel->setPixmap(mSubjectTwoNormalPixmap);
        break;

    default:
        WARNQFI << "Invalid scope =" << scope;
        break;
    }
    update(); show();
}

void ReconPage::setNormal(Vector::FileScope scope, QImage image)
{
    TRACEQFI << Vector::scopeString(scope) << image;
    switch (scope)
    {
    case Vector::Baseline:
        mBaselineNormalPixmap = QPixmap::fromImage(image.
            scaled(cmSize, Qt::KeepAspectRatio,
                   Qt::SmoothTransformation));
        mpBaselineNormalPixmapLabel->
                setPixmap(mBaselineNormalPixmap);
        break;

    case Vector::SubjectOne:
        mSubjectOneNormalPixmap = QPixmap::fromImage(image.
            scaled(cmSize, Qt::KeepAspectRatio,
                   Qt::SmoothTransformation));
        mpSubjectOneNormalPixmapLabel->
                setPixmap(mSubjectOneNormalPixmap);
        break;

    case Vector::SubjectTwo:
        mSubjectTwoNormalPixmap = QPixmap::fromImage(image.
            scaled(cmSize, Qt::KeepAspectRatio,
                   Qt::SmoothTransformation));
        mpSubjectTwoNormalPixmapLabel->
                setPixmap(mSubjectTwoNormalPixmap);
        break;

    default:
        WARNQFI << "Invalid scope =" << scope;
        break;
    }
    update(); show();
}
