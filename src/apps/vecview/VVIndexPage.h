#pragma once

class QGridLayout;


#include <QWidget>

class VVIndexPage : public QWidget
{
    Q_OBJECT
public:
    explicit VVIndexPage(QWidget * parent=nullptr);

public slots:
    void setupGrid(void);


signals:
    void gridSetup(void);

private:
    QGridLayout * mpGrid;

};

