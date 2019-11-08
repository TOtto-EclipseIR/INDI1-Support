#include "BaseMdiMainWindow.h"

BaseMdiMainWindow::BaseMdiMainWindow(QWidget *parent)
    : QMainWindow(parent)
//    , cmpDocManager(new MdiDocumentManager(this))
    , cmpWinManager(new MdiWindowManager(this))
{
    setObjectName("BaseMdiMainWindow");
}
