#ifndef WEBVIEW_H
#define WEBVIEW_H
#include <QWebView>

class ZoomStrip;

class WebView: public QWebView
{
public:
    WebView(QWidget * parent = 0);
protected:
    void resizeEvent(QResizeEvent *e);
private:
    ZoomStrip * zoomStrip_m;
};

#endif // WEBVIEW_H
