TEMPLATE = app
TARGET = flickscroll
SOURCES = flickscroll.cpp \
    main.cpp \
    zoomstrip.cpp \
    webview.cpp
HEADERS = flickscroll.h \
    zoomstrip.h \
    webview.h
QT += network \
    webkit
RESOURCES += flickscroll.qrc
