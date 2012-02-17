#include <QApplication>
#include <QPushButton>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    QPushButton button("Quit");
    button.show();

    QObject::connect(&button, SIGNAL(clicked()),
                     &a, SLOT(quit()));
    return a.exec();
}
