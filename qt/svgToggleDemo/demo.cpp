#include <QApplication>
#include <QtSvgToggleSwitch>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    QtSvgToggleSwitch *toggle = new QtSvgToggleSwitch();
    toggle->setSkin("Beryl");
    toggle->setFixedSize(800,600);
    toggle->show();

    return a.exec();
}
