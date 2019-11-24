#pragma once

#include <QWidget>

#include <QLabel>
#include <QPixmap>

class VVHomeCoverPage : public QWidget
{
    Q_OBJECT
public:
    explicit VVHomeCoverPage(QWidget * parent=nullptr);

public slots:
    void setup(void);

signals:
    void setup(bool success);

private:
    QPixmap mPixmap;
    QLabel mLabel;
};

