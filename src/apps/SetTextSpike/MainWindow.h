#pragma once

#include <QMainWindow>

#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QTabWidget>
#include <QTextEdit>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setup(void);
    void takeAction(void);
    void close(void);

private:
    QWidget * mpMainWidget=nullptr;
    QTabWidget * mpTabWidget=nullptr;
    QLabel * mpHomeLabel=nullptr;
    QTextEdit * mpTextEdit=nullptr;
    QLabel * mpLabel=nullptr;
    QAction * mpTakeAction=nullptr;
    QAction * mpCloseAction=nullptr;
    QAction * mpQuitAction=nullptr;
};
