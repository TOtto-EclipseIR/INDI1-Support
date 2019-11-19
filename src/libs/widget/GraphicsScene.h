#pragma once

#include <QObject>
#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QObject * parent=nullptr);
};

