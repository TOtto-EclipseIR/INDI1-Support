#pragma once

#include <QWidget>

class QGraphicsScene;
class QGraphicsView;

class VectorSetGraphics : public QWidget
{
    Q_OBJECT
public:
    explicit VectorSetGraphics(QWidget * parent=nullptr);
    QGraphicsView * view(void);

public slots:
    void setupWidgets(void);

signals:


private:

    QGraphicsScene * cmpScene;
    QGraphicsView * cmpView;
};

