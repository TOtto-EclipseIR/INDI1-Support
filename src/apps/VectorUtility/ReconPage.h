#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"

#include <QPixmap>
#include <QSize>

class ReconPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit ReconPage(CentralStack * parent);
    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:

protected slots:
    void startSetup(void);
    void finishSetup(void)
    { emit setupFinished(); }
    void setVector(VectorObject * vector) override;
    void clearNormal(const Vector::FileScope scope);
    void setNormal(Vector::FileScope scope, QImage image);

signals:
    void ctorFinished(void);
    void setupFinished(void);

private:
    QLabel * mpBaselineReconPixmapLabel;
    QLabel * mpSubjectOneReconPixmapLabel;
    QLabel * mpSubjectTwoReconPixmapLabel;
    QLabel * mpBaselineNormalPixmapLabel;
    QLabel * mpSubjectOneNormalPixmapLabel;
    QLabel * mpSubjectTwoNormalPixmapLabel;
    const QSize cmSize = QSize(256, 256);
    QPixmap mBaselineReconPixmap;
    QPixmap mSubjectOneReconPixmap;
    QPixmap mSubjectTwoReconPixmap;
    QPixmap mBaselineNormalPixmap;
    QPixmap mSubjectOneNormalPixmap;
    QPixmap mSubjectTwoNormalPixmap;
};

