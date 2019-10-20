#pragma once
#include "Mdi.h"

#include <QMainWindow>

#include "MdiDocumentManager.h"
#include "MdiWindowManager.h"

class MDI_EXPORT BaseMdiMainWindow : public QMainWindow
{
public:
    BaseMdiMainWindow(QWidget * parent=nullptr);

private:
    MdiDocumentManager * cmpDocManager=nullptr;
    MdiWindowManager * cmpWinManager=nullptr;
};

