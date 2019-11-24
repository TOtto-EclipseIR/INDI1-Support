#pragma once

#include <QTabWidget>

class VVMainWindow;
class VVHomeCoverPage;
class VVIndexPage;

class VVHomeStack : public QTabWidget
{
    Q_OBJECT
public:
    explicit VVHomeStack(VVMainWindow * parent=nullptr);

public slots:
    void setupPages(void);

signals:
    void pagesSetup(void);

private:
    VVMainWindow * cmpMainWindow=nullptr;
    VVHomeCoverPage * mpHomePage=nullptr;
    VVIndexPage * mpIndexPage=nullptr;
};

