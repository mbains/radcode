#ifndef CREATOR_EXAMPLE_H
#define CREATOR_EXAMPLE_H

#include <QtGui/QDialog>

namespace Ui
{
    class creator_example;
}

class myDialog : public QDialog
{
    Q_OBJECT

public:
    myDialog(QWidget *parent = 0);
    ~myDialog();

private:
    Ui::creator_example *ui;
};

#endif // CREATOR_EXAMPLE_H
