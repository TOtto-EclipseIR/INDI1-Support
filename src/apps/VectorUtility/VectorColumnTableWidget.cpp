#include "VectorColumnTableWidget.h"

#include <QTimer>

#include "Debug.h"
#include "UnitFloat.h"
#include "UnitFloatLabel.h"
#include "VectorColumn.h"
#include "VectorColumnTwig.h"

VectorColumnTableWidget::VectorColumnTableWidget(const int rows,
                                                 QWidget * parent)
    : QTableWidget(parent)
    , mRows(rows)
    , mCols(VectorColumn::numColumns())
{
    TRACEFN()
    setObjectName("VectorColumnTableWidget");
    QTimer::singleShot(100, this, &VectorColumnTableWidget::fillHeaders);
}

void VectorColumnTableWidget::setFillDefaults()
{
    WANTDO("defaults");
}

void VectorColumnTableWidget::fillHeaders(void)
{
    TRACEFN()
    QStringList vertQsl, horzQsl;
    horzQsl << "";

    for (int r = 1; r <= mRows; ++r)
        vertQsl << QString::number(r);

    foreach (VectorColumnRole::Column col,
             VectorColumnRole::allColumns())
        horzQsl << VectorColumnRole::columnName(col)
                    .replace(' ', '\n');

    setHorizontalHeaderLabels(horzQsl);
    setVerticalHeaderLabels(vertQsl);
    update(); show();
}

void VectorColumnTableWidget::fillTable(void)
{
    TRACEQFI << mRows << mCols;
    setRowCount(mRows), setColumnCount(mCols);
    hideRow(0), hideColumn(0);
    for (int c = 1; c <= mCols; ++c)
    {
        VectorColumnTwig * colTwig = fillTwig(c);
        for (int r = 0; r < mRows; ++r)
        {
            VectorColumnTwig * twig = colTwig->clone();
            setItem(r, c, twig);
        }
        showColumn(c);
    }
    for (int r = 0; r < mRows; ++r) showRow(r);
    update(); show();
}

void VectorColumnTableWidget::setUnitVector(int colIndex,
                                         UnitFloatVector values)
{
    TRACEQFI << colIndex << values.values().first(10);
    int rowCount = values.size();
    UnitFloatLabel ufl;
    for (int row = 0; row < rowCount; ++row)
    {
        UnitFloat::Value value = values.at(row);
        ufl.set(value);
#if 1
        QTableWidgetItem * twig = item(row, colIndex);
        twig->setText(ufl.formatUnit());
#else
        VectorColumnTwig * twig = new VectorColumnTwig(value,
                                     VectorColumnTwig::UnitType);
        twig->setFlags(Qt::ItemNeverHasChildren);
        twig->setData(Qt::DisplayRole, ufl.formatUnit());
        setItem(row, colIndex, twig);
#endif
    }
    TRACEQFI << "exit";
}

VectorColumnTwig * VectorColumnTableWidget::fillTwig(const int col)
{
    VectorColumnTwig::ItemType it = VectorColumnTwig::typeFor(VectorColumnRole::Column(col));
    VectorColumnTwig * twig = new VectorColumnTwig(it);
    twig->setFlags(Qt::ItemNeverHasChildren);
    twig->setFont(twig->font());
    twig->setText(" -0- ");
    twig->setTextAlignment(Qt::AlignBottom | Qt::AlignRight);

    //WANTDO("more?");
    return twig;
}


VectorColumnTableWidget::Parms::Parms(const QVariantMap & settings)
{
    TRACEFN()
    set(settings);
}

void VectorColumnTableWidget::Parms::set(const QVariantMap & settings)
{
    TRACEFN()
    mSettings = settings;
}

void VectorColumnTableWidget::Parms::replace(const QString & key,
                                     const QVariant & setting)
{
    TRACEQFI << key << setting;
    mSettings.insert(key, setting);
}

void VectorColumnTableWidget::Parms::replace(const QVariantMap & settings)
{
    TRACEFN()
    foreach(QString key, settings.keys())
            replace(key, settings.value(key));
}

QVariant VectorColumnTableWidget::Parms::value(const QString & key,
                                const QVariant & defValue) const
{
    QVariant var = mSettings.value(key, defValue);
    TRACEQFI << key << var;
    return var;
}

