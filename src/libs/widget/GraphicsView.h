#pragma once

#include <QWidget>
#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget * parent=nullptr);
};

