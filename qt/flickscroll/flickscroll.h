#ifndef FLICKSCROLL_H
#define FLICKSCROLL_H

#include <QObject>
#include <QMouseEvent>

class FlickScrollPrivate;
class QWebView;
struct FlickData;

//this is the borderline between pressed and moved
#define CURSOR_MOVEMENT_THRESHOLD 5

class FlickScroll: public QObject
{
    Q_OBJECT
public:
    FlickScroll(QObject *parent = 0);
    ~FlickScroll();
    void activateOn(QWebView *widget);
    void deactivateFrom(QWebView *widget);
    bool eventFilter(QObject *object, QEvent *event);
    void fakeMouseEvent(QMouseEvent *mouseEvent, FlickData *data, QObject *object);
    bool checkMouseSteadiness(const QPoint & pressed, const QPoint & released);

protected:
    void timerEvent(QTimerEvent *event);

private:
    FlickScrollPrivate *flickScroll_pm;
};
#endif
