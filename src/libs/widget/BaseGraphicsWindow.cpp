#include "BaseGraphicsWindow.h"

BaseGraphicsWindow::BaseGraphicsWindow(QWidget * parent)
    : QDockWidget(parent)
    , mAlpha16(0xFFFF)
{
    setObjectName("BaseGraphicsWindow");
}

BaseGraphicsWindow::BaseGraphicsWindow(const quint16 alpha,
                                       QWidget * parent)
    : QDockWidget(parent)
    , mAlpha16(alpha)
{

}
