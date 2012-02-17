#ifndef ZOOMSTRIP_H
#define ZOOMSTRIP_H

#include <QWidget>

class ZoomStrip : public QWidget
{
    Q_OBJECT
public:
    ZoomStrip(QWidget * parent = 0);

    QSize sizeHint() const;
    QSize minimumSizeHint() const;

signals:
    void zoomInClicked();
    void zoomOutClicked();

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent *event);

private:
    QPixmap zoomInPixmap;
    QPixmap zoomOutPixmap;
};

#endif // ZOOMSTRIP_H
