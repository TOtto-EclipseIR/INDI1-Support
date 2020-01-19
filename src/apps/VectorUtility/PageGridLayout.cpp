#include "PageGridLayout.h"

#include "Debug.h"

PageGridLayout::PageGridLayout(QWidget * parent)
    : QGridLayout(parent)
{

}

QSize PageGridLayout::maximumSize(void) const
{
    TRACEFN()
    MUSTDO("Implement");
    return QSize();
}
