#include "zoomstrip.h"

#include <QtCore>
#include <QtGui>
#include <QPaintEvent>

ZoomStrip::ZoomStrip(QWidget *parent) : QWidget(parent)
{
    zoomInPixmap.load(":/images/list-add.png");
    zoomOutPixmap.load(":/images/list-remove.png");
}

QSize ZoomStrip::sizeHint() const
{
    return minimumSizeHint();
}

QSize ZoomStrip::minimumSizeHint() const
{
    return QSize(40,80);
}

/*handle simple clicks*/
void ZoomStrip::mousePressEvent(QMouseEvent * event)
{
    if(event->pos().y() < height() / 2)
        emit zoomInClicked();
    else
        emit zoomOutClicked();
}

void ZoomStrip::paintEvent(QPaintEvent *event)
{
    int w = width();
    int s = (w - zoomInPixmap.width())/2;

    QPainter p(this);
    p.fillRect(event->rect(), QColor(128, 128, 128, 128));
    p.drawPixmap(s, s, zoomInPixmap);
    p.drawPixmap(s, s+w, zoomOutPixmap);
    p.end();
}
