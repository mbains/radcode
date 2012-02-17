#include "flickscroll.h"
#include <QAbstractScrollArea>
#include <QApplication>
#include <QPoint>
#include <QHash>
#include <QEvent>
#include <QBasicTimer>
#include <QWidget>
#include <QDebug>
#include <QWebView>
#include <QWebFrame>
#include <assert.h>


struct FlickData
{
    typedef enum
    {
        Steady,
        Pressed,
        ManualScroll,
        AutoScroll,
        Stop
    } State;

    State state;
    QWebView *widget;
    QPoint pressPos; //where the mouse was pressed.
    QPoint offset;  //the offset position from javascript
    int extJS_offset; //for custom javascript scrolling function
    QPoint dragPos;
    QPoint speed;
    QList<QEvent *> ignored;
};

class FlickScrollPrivate
{
    //Hold flick data in a hash with key=widget
    public:
    QHash<QWebView *, FlickData*> flickData;
    QBasicTimer ticker;
};


FlickScroll::FlickScroll(QObject *parent): QObject(parent)
{
    flickScroll_pm = new FlickScrollPrivate();
}

void FlickScroll::activateOn(QWebView *webView)
{

        QWebFrame *frame = webView->page()->mainFrame();
        frame->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
        frame->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

        webView->installEventFilter(this);

        int removed = flickScroll_pm->flickData.remove(webView);
        printf("FlickScroll::activateOn removed %d items from hash\n", removed);

        FlickData * newFlickData = new FlickData();
        flickScroll_pm->flickData[webView] = newFlickData;
        newFlickData->widget = webView;
        newFlickData->state = FlickData::Steady;

}

void FlickScroll::deactivateFrom(QWebView *webView)
{
    webView->removeEventFilter(this);

    //call delete on the value pointed to in HASH
    delete flickScroll_pm->flickData[webView];
    //remove the value from the HASH
    flickScroll_pm->flickData.remove(webView);
}

static QPoint scrollOffset(QWebView *webView)
{
    int x = 0;
    int y = 0;

    QWebFrame *frame = webView->page()->mainFrame();
    x = frame->evaluateJavaScript("window.scrollX").toInt();
    y = frame->evaluateJavaScript("window.scrollY").toInt();

    return QPoint(x,y);
}

static void setScrollOffSet(QWebView *webView, const QPoint & point)
{
    QWebFrame *frame = webView->page()->mainFrame();
    //printf("setScrollOffset: %d, %d\n", point.x(), point.y());
    frame->evaluateJavaScript(QString("window.scrollTo(%1,%2);").arg(point.x()).arg(point.y()));
}

static void scrollCustom(QWebView *webView, int value)
{
    QWebFrame * frame = webView->page()->mainFrame();
    //printf("scrollCustom(%d)\n", value);
    frame->evaluateJavaScript(QString("scrollAlarmTabContent(%1)").arg(-value));
}

static QPoint deaccelerate(const QPoint &speed, int a = 1, int max = 64)
{
    //bound speed to -max, and max
    int x = qBound(-max, speed.x(), max);
    int y = qBound(-max, speed.y(), max);

    // if x is 0, return x. if x is positive return x-a as long as its positive (else 0).
    //    if x is negative return x+a as long as its negative ( else 0)
    x = (x == 0) ? x : (x > 0) ? qMax(0, x-a) : qMin(0, x+a);
    y = (y == 0) ? y : (y > 0) ? qMax(0, y-a) : qMin(0, y+a);

    return QPoint(x,y);
}

bool FlickScroll::eventFilter(QObject *object, QEvent *event)
{
    if(!object->isWidgetType())
        return false;

    QEvent::Type type = event->type();
    if(type != QEvent::MouseButtonPress &&
       type != QEvent::MouseButtonRelease &&
       type != QEvent::MouseMove)
        return false;

    //dynamic_cast ensures that event is only a derived event of type QMouseEvent
    QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent *> (event);
    if(!mouseEvent || mouseEvent->modifiers() != Qt::NoModifier)
        return false;

    //check if QObject is a QWebView, get flickdata,
    //return if there are ignored events
    QWebView *webView = dynamic_cast<QWebView *>(object);
    FlickData * data = flickScroll_pm->flickData.value(webView);
    if(!webView || !data || data->ignored.removeAll(event))
        return false;

    //go through the mouse event state machine
    bool consumed = false; // mouse events consumed
    switch(data->state)
    {
        //if mouse is pressed during steady state, goto pressed, cache the position
        // cache the offset.
        case FlickData::Steady:
            if (mouseEvent->type() == QEvent::MouseButtonPress && mouseEvent->buttons() == Qt::LeftButton)
            {
                printf("State = Steady, MouseButtonPress\n");
                consumed = true;
                data->state = FlickData::Pressed;
                data->pressPos = mouseEvent->pos();
                data->offset = scrollOffset(webView);
                data->extJS_offset = mouseEvent->pos().y();
            }
        break;


        case FlickData::Pressed:
            //if the mouse is released during pressed state, goto steady state,
            //add button press and release to ignored events to restimulate button push/release
            if(mouseEvent->type() == QEvent::MouseButtonRelease)
            {
                printf("State = Pressed, MouseButtonRelease\n");
                consumed = true;
                data->state = FlickData::Steady;

                fakeMouseEvent(mouseEvent, data, object);
            }
            //user is manually scrolling.
            //set the state, set the drag position. if ticker is not active, start it.
            else if(mouseEvent->type() == QEvent::MouseMove)
            {
                printf("State = Pressed, MouseMove\n");
                consumed = true;
                data->state = FlickData::ManualScroll;
                data->dragPos = QCursor::pos(); //from cursor for accuracy
                if(!flickScroll_pm->ticker.isActive())
                    flickScroll_pm->ticker.start(20, this);
            }
        break;


        //if manually scrolling, update the delta
        // set the new scrolloffset, by adjusting the previous one with delta
        //if the mouse is released, let it auto scroll
        case FlickData::ManualScroll:
            if(mouseEvent->type() == QEvent::MouseMove)
            {
                printf("State = ManualScroll, MouseMove\n");
                consumed = true;
                QPoint delta = mouseEvent->pos() - data->pressPos;
                setScrollOffSet(data->widget, data->offset - delta);
                scrollCustom(webView, mouseEvent->pos().y() - data->extJS_offset);
                data->extJS_offset = mouseEvent->pos().y();
            }
            if(mouseEvent->type() == QEvent::MouseButtonRelease && !checkMouseSteadiness(mouseEvent->pos(), data->pressPos ))
            {
                printf("State = ManualScroll, MouseButtonRelease\n");
                consumed = true;
                data->state = FlickData::AutoScroll;
            }
            else if(mouseEvent->type() == QEvent::MouseButtonRelease)
            {
                printf("State = ManualScroll, MouseButtonRelease, reverting to steady\n");
                consumed = true;
                data->state = FlickData::Steady;

                fakeMouseEvent(mouseEvent, data, object);
            }
        break;
        case FlickData::AutoScroll:
            /*
              if the mouse is clicked while auto scrolling, we want to stop.
              reset all states.
            */
            if(mouseEvent->type() == QEvent::MouseButtonPress)
            {
                printf("State = AutoScroll, MouseButtonPress\n");
                consumed=true;
                data->state = FlickData::Stop;
                data->speed = QPoint(0,0);
                data->extJS_offset = 0;
                data->pressPos = mouseEvent->pos();
                data->offset = scrollOffset(data->widget);
            }
            if(mouseEvent->type() == QEvent::MouseButtonRelease)
            {
                 printf("State = AutoScroll, MouseButtonRelease\n");
                consumed = true;
                data->state = FlickData::Steady;
                data->speed = QPoint(0,0);
            }
        break;
        case FlickData::Stop:
            if(mouseEvent->type() == QEvent::MouseButtonRelease)
            {
                printf("State = Stop, MouseButtonRelease\n");
                consumed = true;
                data->state = FlickData::Steady;
            }
            if(mouseEvent->type() == QEvent::MouseMove)
            {
                printf("State = Stop, MouseMove\n");
                consumed = true;
                data->state = FlickData::ManualScroll;
                data->dragPos = QCursor::pos();
                if(!flickScroll_pm->ticker.isActive())
                    flickScroll_pm->ticker.start(20, this);
            }
        break;
        default:
        break;
    }

    return consumed;
}

void FlickScroll::fakeMouseEvent(QMouseEvent *mouseEvent, FlickData *data, QObject *object)
{
    QMouseEvent *fakePress = new QMouseEvent(QEvent::MouseButtonPress,//type
                                          data->pressPos, Qt::LeftButton, //pos, button
                                          Qt::LeftButton, Qt::NoModifier); //buttons, keyboard modifiers
    QMouseEvent *fakeRelease = new QMouseEvent(*mouseEvent); //why is it necessary to do this?

    data->ignored << fakePress;
    data->ignored << fakeRelease;
    QApplication::postEvent(object, fakePress);
    QApplication::postEvent(object, fakeRelease);
}

/* On a touch screen, the user isn't able to press/release buttons without moving his finger
    this method checks if the movement is within a tolerance. returns True if the release pos
    is not far enough from the press release to be considered a cursor move
*/
bool FlickScroll::checkMouseSteadiness(const QPoint & pressed, const QPoint & released)
{
    if(abs(pressed.y()-released.y()) < CURSOR_MOVEMENT_THRESHOLD && abs(pressed.x() - released.x()) < CURSOR_MOVEMENT_THRESHOLD)
        return true;
    return false;
}
void FlickScroll::timerEvent(QTimerEvent *event)
{
    int count = 0;
    QHashIterator<QWebView*, FlickData*> item(flickScroll_pm->flickData);
    while(item.hasNext())
    {
        item.next(); //moves the pointer forward
        FlickData *data = item.value();
        //if moving manually, adjust the speed based on
        //the difference of the new cursor position from the old one
        if(data->state == FlickData::ManualScroll)
        {
            count++;
            data->speed = QCursor::pos() - data->dragPos;
            data->dragPos = QCursor::pos();
        }
        else if(data->state == FlickData::AutoScroll)
        {
            count++;
            data->speed = deaccelerate(data->speed);
            QPoint p = scrollOffset(data->widget);
            setScrollOffSet(data->widget, p - data->speed);

            scrollCustom(data->widget, data->speed.y());
            //printf("autoscroll %d\n", data->speed.y());
            if(data->speed == QPoint(0,0))
                data->state = FlickData::Steady;
        }
    }

    if(!count)
        flickScroll_pm->ticker.stop();

    QObject::timerEvent(event);
}

FlickScroll::~FlickScroll()
{
    delete flickScroll_pm;
}
