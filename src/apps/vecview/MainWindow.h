#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget * parent=nullptr,
               Qt::WindowFlags flags=Qt::WindowFlags());
    ~MainWindow();

private:

};
