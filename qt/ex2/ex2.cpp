#include<QApplication>
#include<QGridLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;

    QGridLayout * mainLayout = new QGridLayout(&window);
    QLabel * label1 = new QLabel("one");
    QLabel * label2 = new QLabel("two");
    QLabel * label3 = new QLabel("three");
    QLabel * label4 = new QLabel("four");
    QLabel * label5 = new QLabel("five");
    QLabel * label6 = new QLabel("six");

    mainLayout->addWidget(label1, 0, 0);
    mainLayout->addWidget(label2, 0, 1);
    mainLayout->addWidget(label3, 1, 0);
    mainLayout->addWidget(label4, 1, 1);
    mainLayout->addWidget(label5, 2, 0);
    mainLayout->addWidget(label6, 2, 1);

    window.show();
    return a.exec();
}
