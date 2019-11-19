#pragma once

#include <QWidget>
class QTabWidget;
class QTextEdit;

class VectorSetDocument;
class VectorSetGraphics;

class VectorSetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VectorSetWidget(VectorSetDocument * doc);

public slots:
    void setupWidget(void);


signals:


private:
    const VectorSetDocument * cmpDocument=nullptr;
    const QTabWidget * cmpMainTabWidget=nullptr;
    const QTextEdit * cmpRawXmlPage=nullptr;
    const VectorSetGraphics * cmpGraphicsPage=nullptr;
};


