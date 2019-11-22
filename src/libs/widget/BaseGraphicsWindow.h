// file: ./src/libs/widget/BaseGraphicsWindow.h
#pragma once
#include "Widget.h"

#include <QSize>
#include <QString>
#include <QWidget>
#include <QDockWidget>

class WIDGET_EXPORT BaseGraphicsWindow : public QDockWidget
{
    Q_OBJECT
public:
    BaseGraphicsWindow(const QString & title=QString(),
                       const QSize clientSize=QSize(),
                       const quint16 alpha=0xFFFF,
                       QWidget * parent=nullptr);
    void set(const QPixmap & pixmap);

    QString title() const;
    void setTitle(const QString &title);
    QSize minimumSize() const;
    void setMinimumSize(const QSize &minimumSize);
    quint16 alpha16() const;
    void setAlpha16(const quint16 &alpha16);

private:
    QString mTitle;
    QSize mMinimumSize;
    quint16 mAlpha16;
};

