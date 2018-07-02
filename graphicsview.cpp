#include "graphicsview.h"

graphicsview::graphicsview(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void graphicsview::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
        emit rightClicked();
    else
        emit leftClicked();
}

void graphicsview::mouseMoveEvent(QMouseEvent *e)
{
    emit mouseMove(e->pos());
}

void graphicsview::toggleMouseTracking(bool m)
{
    if (m)
        setMouseTracking(true);
    else
        setMouseTracking(false);
}
