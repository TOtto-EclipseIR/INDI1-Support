#include "SummaryPage.h"

#include <QTimer>

#include "Debug.h"
#include "SummaryView.h"

SummaryPage::SummaryPage(CentralStack * parent)
    : AbstractCentralPage(parent)
{
    TRACEFN()
    setObjectName("SummaryPage");
    connect(this, &SummaryPage::ctorFinished,
            this, &SummaryPage::startSetup);

    mViewVector.resize(Vector::sizeScope);
    mViewVector[Vector::Baseline]
            = new SummaryView(Vector::Baseline, this);
    mViewVector[Vector::SubjectOne]
            = new SummaryView(Vector::SubjectOne, this);
    mViewVector[Vector::SubjectTwo]
            = new SummaryView(Vector::SubjectTwo, this);
    TSTALLOC(mViewVector[Vector::Baseline]);
    TSTALLOC(mViewVector[Vector::SubjectOne]);
    TSTALLOC(mViewVector[Vector::SubjectTwo]);


    emit ctorFinished();
    //    QTimer::singleShot(100, this, &BlankPage::setup0);
}

Vector::View SummaryPage::view() const
{
    return Vector::Summary;
}

QString SummaryPage::pageName(void) const
{
    return QString("Summary");
}

void SummaryPage::setVector(VectorObject * vector)
{
    TRACEQFI << vector->scopeString();
    Vector::FileScope scope = vector->scope();
    mViewVector[scope]->setVector(vector);
    update();
    show();
}

void SummaryPage::startSetup(void)
{
    TRACEFN()

    QLabel * BaselineLabel = new QLabel;
    QLabel * SubjectOneLabel = new QLabel;
    QLabel * SubjectTwoLabel = new QLabel;
    QLabel * BaseOneLabel = new QLabel;
    QLabel * BaseTwoLabel = new QLabel;
    QLabel * OneTwoLabel = new QLabel;
    BaselineLabel->setText("Baseline");
    SubjectOneLabel->setText("SubjectOne");
    SubjectTwoLabel->setText("SubjectTwo");
    BaseOneLabel->setText("Base/One");
    BaseTwoLabel->setText("Base/Two");
    OneTwoLabel->setText("One/Two");
    layout()->addWidget(BaselineLabel, 2, 0);
    layout()->addWidget(mViewVector[Vector::Baseline], 2, 1, 1, 3);
    layout()->addWidget(SubjectOneLabel, 4, 0);
    layout()->addWidget(mViewVector[Vector::SubjectOne], 4, 1, 1, 3);
    layout()->addWidget(SubjectTwoLabel, 6, 0);
    layout()->addWidget(mViewVector[Vector::SubjectTwo], 6, 1, 1, 3);
    layout()->addWidget(BaseOneLabel, 8, 0);
    layout()->addWidget(BaseTwoLabel, 10, 0);
    layout()->addWidget(OneTwoLabel, 12, 0);
    update();
    show();
    finishSetup();
}

