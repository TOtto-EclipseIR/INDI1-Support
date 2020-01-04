#pragma once

#include <QWidget>

#include "AbstractCentralPage.h"
#include "VectorTableModel.h"
#include "VectorTableView.h"


class GridPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit GridPage(CentralStack * parent,
                       const int flags=0);
    virtual QString pageName(void) const override;
    void setModel(VectorTableModel * model);

public slots:




signals:

protected slots:
    void setupModel(void);
    void setupViews(void);

private:
    VectorTableModel * mpTableModel=nullptr;
    VectorTableView * mpTableView=nullptr;

};

