#pragma once

#include <QWidget>
#include <QTableWidget>

#include "UnitFloatVector.h"
#include "VectorColumn.h"
#include "VectorColumnTwig.h"

class VectorColumnTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    class Parms
    {
    public:
        Parms(void) {}
        Parms(const QVariantMap & settings);
        void set(const QVariantMap & settings);
        void replace(const QString & key, const QVariant & setting);
        void replace(const QVariantMap & settings);
        QVariant value(const QString & key,
                       const QVariant & defValue=QVariant()) const;
    private:
        QVariantMap mSettings;

    };

public:
    explicit VectorColumnTableWidget(const int rows,
                                     QWidget * parent=nullptr);

    void setRows(const int rows)
    { mRows = rows; }
    void configure(const QVariantMap & settings)
    { mParms.replace(settings); }

public slots:
    void setFillDefaults(void);
    void fillHeaders(void);
    void fillTable(void);
    void setUnitVector(int colIndex, UnitFloatVector values);

protected:
    VectorColumnTwig * fillTwig(const int col);

signals:

private:
    int mRows=0;
    int mCols=0;
    Parms mParms;

};

