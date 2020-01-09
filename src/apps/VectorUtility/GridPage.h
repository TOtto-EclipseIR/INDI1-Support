#pragma once

#include <QWidget>

#include <QHeaderView>

#include "AbstractCentralPage.h"
#include "VectorTableModel.h"
#include "VectorTableView.h"


class GridPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit GridPage(CentralStack * parent,
                       const int flags=0);
    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;
    void setModel(VectorTableModel * model);

public slots:




signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

protected slots:
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }
    void setupViews(void);

private:
    VectorTableModel * mpTableModel=nullptr;
    VectorTableView * mpTableView=nullptr;
    QHeaderView * mpHeaderView=nullptr;
};

