#pragma once

#include <QWidget>
#include <QGridLayout>

//#include <QLabel>
class QTextEdit;

#include "Vector.h"
class VectorObject;

class SummaryView : public QWidget
{
    Q_OBJECT
public:
    explicit SummaryView(const Vector::FileScope scope,
                         QWidget * parent=nullptr);

public slots:
    void setupLayout(void);
    void setVector(VectorObject * vector);

protected slots:

signals:
    void layoutSetup(Vector::FileScope);

private:
    const Vector::FileScope cmScope;
    QGridLayout * mpGridLayout=nullptr;
    QTextEdit * mpFileNameText;
    QTextEdit * mpDirNameText;
    QTextEdit * mpFileSizeText;
};

