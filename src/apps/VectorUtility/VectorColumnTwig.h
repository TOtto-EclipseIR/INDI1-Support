#pragma once

#include <QWidget>
#include <QTableWidgetItem>

#include <QBrush>
#include <QColor>
#include <QLine>
#include <QMargins>
#include <QPainter>
#include <QPen>
#include <QPixmap>
#include <QString>
#include <QVariant>
#include <QVariantMap>
#include <QVector>

#include "VectorColumn.h"

class VectorColumnTwig : public QTableWidgetItem
{
public:
    enum ItemType
    {
        userNull = QTableWidgetItem::UserType,
        IndexType,
        UnitType,
        DeltaType,
        RatioType,
        userCeiling
    };

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
    explicit VectorColumnTwig(void);
    explicit VectorColumnTwig(const ItemType type=userNull);
    explicit VectorColumnTwig(const QString text,
                              const ItemType type);
    explicit VectorColumnTwig(const int iValue,
                              const ItemType type);
    explicit VectorColumnTwig(const qreal rValue,
                              const ItemType type);
    void configure(const QVariantMap & settings)
    { mParms.replace(settings); }

    virtual VectorColumnTwig * clone(void) const;

    QFont font(void);

public: // static
    static ItemType typeFor(const VectorColumnRole::Column col);


private:
    ItemType cmType=userNull;
    QString mText;
    int mInt=0;
    qreal mReal=0.0;
    Parms mParms;

signals:

};

