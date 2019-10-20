#pragma once

#include <QObject>

#include <QFileInfo>

class BaseDocument : public QObject
{
    Q_OBJECT
public:
    explicit BaseDocument(QObject * parent=nullptr);

public slots:
    void newFile(void) {;}
    void openFile(const QFileInfo & fi) {;}
    void saveFile(void) {;}
    void saveFileAs(const QFileInfo & fi) {;}
    void fileOpenDialog(void) {;}
    void fileSaveAsDialog(void) {;}

signals:

private:

};

