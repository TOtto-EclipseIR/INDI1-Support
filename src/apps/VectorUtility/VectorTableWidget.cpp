#include "VectorTableWidget.h"

#include "VectorItemDelegate.h"
#include "VectorTableHorizontalHeader.h"
#include "VectorTableView.h"
#include "VectorTableVerticalHeader.h"

VectorTableWidget::VectorTableWidget(QWidget * parent)
    : QTableWidget(parent)
    , mpTableView(new VectorTableView(this))
    , mpVerticalHeader(new VectorTableVerticalHeader(this))
    , mpHorizontalHeader(new VectorTableHorizontalHeader(this))
    , mpItemDelegate(new VectorItemDelegate(this))

{
    setObjectName("VectorTableWidget");
}
