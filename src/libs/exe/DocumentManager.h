// ./src/libs/exe/DocumentManager.h
#pragma once
#include <QObject>

class DocumentManager : public QObject
{
    Q_OBJECT
public:
    explicit DocumentManager(QObject * parent=nullptr);


public slots:

signals:

private:

};

/*
public slots:
    void newFile(void) {;}
    void openFile(const QFileInfo & fi) {;}
    void saveFile(void) {;}
    void saveFileAs(const QFileInfo & fi) {;}
    void fileOpenDialog(void) {;}
    void fileSaveAsDialog(void) {;}

signals:
  */
