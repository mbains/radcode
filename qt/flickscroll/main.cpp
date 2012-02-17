#include <QtCore>
#include <QtGui>
#include <QtWebKit>
#include "flickscroll.h"
#include "webview.h"

int main(int argc, char *argv[])
{

    QApplication::setGraphicsSystem("raster");
    QApplication app(argc, argv);
    WebView * webview = new WebView();
    webview->setUrl(QUrl("http://www.google.com"));
    webview->resize(400,300);
    FlickScroll * flickscroll = new FlickScroll(webview);
    flickscroll->activateOn(webview);
    webview->show();

    return app.exec();
}
