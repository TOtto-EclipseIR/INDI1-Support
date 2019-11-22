#pragma once

#include <QWidget>

class QLabel;
class QTabWidget;
class QTextEdit;

class VectorSetDocument;
class VectorSetGraphics;
class VectorSetSummaryPage;

class VectorSetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VectorSetWidget(VectorSetDocument * doc);

    QLabel * label(void) { return mpLabel; }

public slots:
    void setupWidget(void);


signals:


private:
    const VectorSetDocument * cmpDocument=nullptr;
    const QTabWidget * cmpMainTabWidget=nullptr;
    const QTextEdit * cmpRawXmlPage=nullptr;
    const VectorSetSummaryPage * cmpSummaryPage=nullptr;
    const VectorSetGraphics * cmpGraphicsPage=nullptr;

    QLabel * mpLabel=nullptr;
};


