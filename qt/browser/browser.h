#ifndef BROWSER_H
#define BROWSER_H

#include <QtGui/QMainWindow>

namespace Ui
{
    class browser;
}

class browser : public QMainWindow
{
    Q_OBJECT

public:
    browser(QWidget *parent = 0);
    ~browser();

private:
    Ui::browser *ui;

private slots:
    void on_webView_loadStarted();
    void openUrl();
};

#endif // BROWSER_H
