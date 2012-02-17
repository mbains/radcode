#include "browser.h"
#include "ui_browser.h"

browser::browser(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::browser)
{
    ui->setupUi(this);
}

browser::~browser()
{
    delete ui;
}

void browser::on_webView_loadStarted()
{

}

void browser::openUrl(void)
{
}
