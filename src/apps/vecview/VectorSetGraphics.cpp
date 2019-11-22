#include "VectorSetGraphics.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include "../../libs/base/Debug.h"

VectorSetGraphics::VectorSetGraphics(QWidget * parent)
    : QWidget(parent)
    , cmpScene(new QGraphicsScene)
    , cmpView(new QGraphicsView(cmpScene))
{
    TRACEFN()


}

void VectorSetGraphics::setupWidgets()
{
    TRACEFN()

}
