#pragma once

#include <QMainWindow>

class VVMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    VVMainWindow(QWidget * parent=nullptr,
               Qt::WindowFlags flags=Qt::WindowFlags());
    ~VVMainWindow();

private:

};
