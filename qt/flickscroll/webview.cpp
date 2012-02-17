#include "webview.h"
#include "zoomstrip.h"
#include <stdio.h>

WebView::WebView(QWidget * parent): QWebView(parent)
{
    zoomStrip_m = new ZoomStrip(this);
    printf("height = %d\n", height());
}

void WebView::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    int h  = zoomStrip_m->sizeHint().height();
    zoomStrip_m->move(0, (height() - h)/2);
}
