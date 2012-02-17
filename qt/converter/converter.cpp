#include <QApplication>
#include "byteconverterdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ByteConverterDialog bc;
    bc.setAttribute(Qt::WA_QuitOnClose);
    bc.show();
    return a.exec();
}
