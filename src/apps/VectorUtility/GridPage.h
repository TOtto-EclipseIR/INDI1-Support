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
    explicit GridPage(CentralStack * parent,
                       const int flags=0);
    virtual Vector::View view(void) const override;
    virtual QString pageName(void) const override;

public slots:
    void setIndex(int indexColumn, int rowCount);
    void setVector(VectorObject * vector) override;

protected slots:
    void startSetup(QObject * thisObject);
    void finishSetup(QObject * thisObject)
    { Q_UNUSED(thisObject); emit setupFinished(this); }
    void setupViews(void);

signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);

private:
    VectorColumnTableWidget * mpTableWidget=nullptr;
};

