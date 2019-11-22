#include "BaseGraphicsWindow.h"

BaseGraphicsWindow::BaseGraphicsWindow(const QString &title,
                                       const QSize clientSize,
                                       const quint16 alpha,
                                       QWidget * parent)
    : QDockWidget(parent)
    , mTitle(title)
    , mMinimumSize(clientSize)
    , mAlpha16(alpha)
{
    setObjectName("BaseGraphicsWindow");
}

void BaseGraphicsWindow::set(const QPixmap &pixmap)
{

}

QString BaseGraphicsWindow::title() const
{
    return mTitle;
}

void BaseGraphicsWindow::setTitle(const QString &title)
{
    mTitle = title;
}

QSize BaseGraphicsWindow::minimumSize() const
{
    return mMinimumSize;
}

void BaseGraphicsWindow::setMinimumSize(const QSize &minimumSize)
{
    mMinimumSize = minimumSize;
}

quint16 BaseGraphicsWindow::alpha16() const
{
    return mAlpha16;
}

void BaseGraphicsWindow::setAlpha16(const quint16 &alpha16)
{
    mAlpha16 = alpha16;
}
