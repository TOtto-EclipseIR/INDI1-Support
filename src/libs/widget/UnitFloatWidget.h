#pragma once

#include <QWidget>
#include <QLabel>

#include <QBrush>
#include <QFont>
#include <QPen>

#include "../core/UnitFloat.h"

class UnitFloatWidget : public QLabel
{
    Q_OBJECT
public:
    explicit UnitFloatWidget(QWidget * parent=nullptr);
    UnitFloatWidget(const QFont & defaultFont,
                    QWidget * parent=nullptr);
    UnitFloatWidget(const UnitFloat & floatValue,
                    const int decimals,
                    QWidget * parent=nullptr);

public:


public slots:

public: // statics
    static void setDefaultFont(const QFont defaultFont)
    { smDefaultFont = defaultFont; }


signals:

private:
    void ctor(void);

private:
    QBrush mBrush;
    QFont mFont;
    QPen mPen;
    int mDecimals;
    UnitFloat mUnitFloat;
    // mLabel;

private: // statics
    static QFont smDefaultFont;
};

