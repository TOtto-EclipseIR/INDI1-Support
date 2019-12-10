#include "MainWindow.h"

#include <QtDebug>
#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QMenuBar>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mpMainWidget(new QWidget)
    , mpTabWidget(new QTabWidget)
    , mpHomeLabel(new QLabel(mpMainWidget))
    , mpTextEdit(new QTextEdit(mpMainWidget))
    , mpLabel(new QLabel(mpMainWidget))
{
    qDebug() << Q_FUNC_INFO;
    QTimer::singleShot(2000, this, SLOT(setup()));
}

MainWindow::~MainWindow()
{
    qDebug() << Q_FUNC_INFO;
}

void MainWindow::setup()
{
    qDebug() << Q_FUNC_INFO;


    mpHomeLabel->setFont(QFont("Times", 48, QFont::Bold));
    mpHomeLabel->setText("Home");
    mpTextEdit->setPlainText("QTextEdit widget");
    mpLabel->setTextFormat(Qt::PlainText);
    mpLabel->setText("QLabel widget");


    QGridLayout * pageLayout = new QGridLayout(mpMainWidget);
    pageLayout->addWidget(mpTextEdit, 0, 0);
    pageLayout->addWidget(mpLabel, 1, 0);
    mpMainWidget->setLayout(pageLayout);
#if true
    mpMainWidget->setLayout(pageLayout);
    mpTabWidget->addTab(mpHomeLabel, "&Home");
    mpTabWidget->addTab(mpMainWidget, "&Main");
    QMainWindow::setCentralWidget(mpTabWidget);
#else
    pageLayout->addWidget(mpHomeLabel, 2, 0);
    mpMainWidget->setLayout(pageLayout);
    QMainWindow::setCentralWidget(mpMainWidget);
#endif

    QMenu * takeMenu = menuBar()->addMenu("&Take");
    mpTakeAction = takeMenu->addAction("&Action");
    mpCloseAction = takeMenu->addAction("&Close");
    mpQuitAction = takeMenu->addAction("&Quit");

    connect(mpTakeAction, &QAction::triggered,
            this, &MainWindow::takeAction);
    connect(mpCloseAction, &QAction::triggered,
            this, &MainWindow::close);
    connect(mpQuitAction, &QAction::triggered,
            qApp, &QApplication::quit);
}

void MainWindow::takeAction()
{
    qDebug() << Q_FUNC_INFO;
    mpTextEdit->setPlainText("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    mpLabel->setText("Lorem ipsum");
}

void MainWindow::close()
{
    qDebug() << Q_FUNC_INFO;
    mpTextEdit->clear();
    mpLabel->clear();
}

