#include "VectorSetGraphics.h"

#include <QGraphicsScene>
#include <QGraphicsView>


VectorSetGraphics::VectorSetGraphics(QWidget * parent)
    : QWidget(parent)
    , cmpScene(new QGraphicsScene)
    , cmpView(new QGraphicsView(cmpScene))
{


}

void VectorSetGraphics::setupWidgets()
{

}
