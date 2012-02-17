#include <QtGui/QApplication>
#include "creator_example.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myDialog w;
    w.show();
    return a.exec();
}
