#include "creator_example.h"
#include "ui_creator_example.h"

myDialog::myDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::creator_example)
{
    ui->setupUi(this);
}

myDialog::~myDialog()
{
    delete ui;
}
