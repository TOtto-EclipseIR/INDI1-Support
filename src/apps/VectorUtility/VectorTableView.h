#pragma once

#include <QWidget>
#include <QTableView>

class VectorTableView : public QTableView
{
    Q_OBJECT
public:
    explicit VectorTableView(QWidget * parent=nullptr);

public slots:




signals:
    void ctorFinished(QObject * thisObject);
    void setupFinished(QObject * thisObject);


private:

};

