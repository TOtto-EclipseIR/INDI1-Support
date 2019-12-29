#pragma once

#include <QWidget>
#include <QLabel>

#include <QColor>

#include "UnitFloat.h"

class UnitFloatLabel : public QLabel
{
    Q_OBJECT
public:
    explicit UnitFloatLabel(QWidget * parent=nullptr);
    explicit UnitFloatLabel(const UnitFloat value,
                            QWidget * parent=nullptr);
    explicit UnitFloatLabel(const UnitFloat value,
                            const QColor & baseColor,
                            QWidget * parent=nullptr);
    void set(const UnitFloat::Value uf);
    void setUnitText(void);

    static qreal getEpsilon();
    static void setEpsilon(const qreal &value);

public slots:

protected:
    QString formatUnit(const int decimals=4,
                       const bool forceSign=true);
    QChar sign(void);


signals:


private:
    UnitFloat::Value mUFV;
    unsigned mFraction;
    QColor mBaseColor;
    static qreal smEpsilon;
};

