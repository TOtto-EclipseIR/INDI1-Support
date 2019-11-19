// file: ./src/libs/widget/BaseGraphicsWindow.h
#pragma once
#include "Widget.h"

#include <QWidget>
#include <QDockWidget>

class WIDGET_EXPORT BaseGraphicsWindow : public QDockWidget
{
    Q_OBJECT
public:
    BaseGraphicsWindow(QWidget * parent=nullptr);
    BaseGraphicsWindow(const quint16 alpha,
                       QWidget * parent=nullptr);

private:
    quint16 mAlpha16 = 0xFFFF;
};

