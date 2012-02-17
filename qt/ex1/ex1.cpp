//example from The book of qt4, art of building qt apps
//
#include<QApplication>
#include<QVBoxLayout>
#include<QLabel>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   QWidget window;

   QVBoxLayout * mainLayout = new QVBoxLayout(&window);
   QLabel * label1 = new QLabel("One");
   QLabel * label2 = new QLabel("Two");

   mainLayout->addWidget(label1);
   mainLayout->addWidget(label2);

   window.show();
   return a.exec();
}
