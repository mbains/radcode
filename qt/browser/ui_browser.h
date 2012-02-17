/********************************************************************************
** Form generated from reading UI file 'browser.ui'
**
** Created: Thu May 19 11:09:20 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BROWSER_H
#define UI_BROWSER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_browser
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QWebView *webView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *browser)
    {
        if (browser->objectName().isEmpty())
            browser->setObjectName(QString::fromUtf8("browser"));
        browser->resize(596, 400);
        centralWidget = new QWidget(browser);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 591, 341));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        webView = new QWebView(horizontalLayoutWidget);
        webView->setObjectName(QString::fromUtf8("webView"));
        webView->setAutoFillBackground(false);
        webView->setUrl(QUrl("http://www.google.com/"));

        horizontalLayout->addWidget(webView);

        browser->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(browser);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 596, 26));
        browser->setMenuBar(menuBar);
        mainToolBar = new QToolBar(browser);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        browser->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(browser);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        browser->setStatusBar(statusBar);

        retranslateUi(browser);

        QMetaObject::connectSlotsByName(browser);
    } // setupUi

    void retranslateUi(QMainWindow *browser)
    {
        browser->setWindowTitle(QApplication::translate("browser", "browser", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class browser: public Ui_browser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROWSER_H
