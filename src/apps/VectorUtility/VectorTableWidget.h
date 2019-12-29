#pragma once

#include <QWidget>
#include <QTableWidget>

class VectorTableView;
class VectorTableVerticalHeader;
class VectorTableHorizontalHeader;
class VectorItemDelegate;

class VectorTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit VectorTableWidget(QWidget * parent=nullptr);


public slots:




signals:



private:
    VectorTableView * mpTableView=nullptr;
    VectorTableVerticalHeader * mpVerticalHeader=nullptr;
    VectorTableHorizontalHeader * mpHorizontalHeader=nullptr;
    VectorItemDelegate * mpItemDelegate=nullptr;

};

