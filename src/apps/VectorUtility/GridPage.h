#pragma once

#include <QWidget>
#include "AbstractCentralPage.h"

#include <QTableWidget>

#include "VectorColumn.h"
#include "VectorColumnTableWidget.h"


class GridPage : public AbstractCentralPage
{
    Q_OBJECT
public:
    explicit GridPage(CentralStack * parent);
    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:
    void setVector(VectorObject * vector) override;

protected slots:
    void startSetup(void);
    void finishSetup(void)
    { emit setupFinished(); }
    void setupViews(void);

signals:
    void ctorFinished(void);
    void setupFinished(void);

private:
    VectorColumnTableWidget * mpTableWidget=nullptr;
};

