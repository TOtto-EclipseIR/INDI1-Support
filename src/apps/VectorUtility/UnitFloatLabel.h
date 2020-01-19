#pragma once

#include <QWidget>
#include <QLabel>

#include <QColor>
#include <QFont>

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
    QString formatUnit(const int decimals=4,
                       const bool forceSign=true);


public: // static
    static qreal getEpsilon();
    static void setEpsilon(const qreal &value);
    static void setFont(const QFont & font)
    { smFont = font; }
    static void setDecimals(const int decimals)
    { smDecimals = decimals; }
    virtual QSize sizeHint(void) const override;
    virtual QSize minimumSizeHint() const override
    { return sizeHint(); }

public slots:

protected:
    QChar sign(void);


signals:


private:
    UnitFloat::Value mUFV;
    unsigned mFraction;
    QColor mBaseColor;


private: // static
    static qreal smEpsilon;
    static QFont smFont;
    static int smDecimals;
};

