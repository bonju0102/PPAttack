#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QPoint>

class graphicsview : public QGraphicsView
{
    Q_OBJECT
public:
    graphicsview(QWidget *parent = 0);
public slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void toggleMouseTracking(bool m);
signals:
    void rightClicked();
    void leftClicked();
    void mouseMove(QPoint pos);
};

#endif // GRAPHICSVIEW_H
