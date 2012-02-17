#include "byteconverterdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QIntValidator>

ByteConverterDialog::ByteConverterDialog()
{
    //specifiy dialog as parent for main Layout
    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    QGridLayout * editLayout = new QGridLayout;
    QHBoxLayout * buttonLayout = new QHBoxLayout;

    mainLayout->addLayout(editLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    QLabel * decLabel = new QLabel(tr("Decimal"));
    QLabel * hexLabel = new QLabel(tr("Hex"));
    QLabel * binLabel = new QLabel(tr("Binary"));

    decEdit = new QLineEdit;
    hexEdit = new QLineEdit;
    binEdit = new QLineEdit;

    editLayout->addWidget(decLabel, 0, 0);
    editLayout->addWidget(decEdit, 0, 1);
    editLayout->addWidget(hexLabel, 1, 0);
    editLayout->addWidget(hexEdit, 1, 1);
    editLayout->addWidget(binLabel, 2, 0);
    editLayout->addWidget(binEdit, 2, 1);

    QPushButton * exitButton = new QPushButton(tr("Quit"));
    buttonLayout->addStretch();
    buttonLayout->addWidget(exitButton);

    exitButton->setDefault(true);
                                                    //min, max, parent
    QIntValidator * decValidator = new QIntValidator(0, 255, decEdit);
    decEdit->setValidator(decValidator);

    QRegExpValidator * hexValidator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,2}"), hexEdit);
    hexEdit->setValidator(hexValidator);

    QRegExpValidator * binValidator = new QRegExpValidator(QRegExp("[01]{1,8}"), binEdit);
    binEdit->setValidator(binValidator);

    connect(exitButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(decEdit, SIGNAL(textChanged(const QString &)), this, SLOT(decChanged(const QString &)));
    connect(binEdit, SIGNAL(textChanged(const QString &)), this, SLOT(binChanged(const QString &)));
    connect(hexEdit, SIGNAL(textChanged(const QString &)), this, SLOT(hexChanged(const QString &)));

    setWindowTitle(tr("Byte Converter"));
}

void ByteConverterDialog::decChanged(const QString & newValue)
{
    bool ok;
    int num = newValue.toInt(&ok);
    if(ok)
    {
        hexEdit->setText(QString::number(num, 16));
        binEdit->setText(QString::number(num, 2));
    } else {
        hexEdit->setText("");
        binEdit->setText("");
    }
}

void ByteConverterDialog::hexChanged(const QString & newValue)
{
    bool ok;
    int num = newValue.toInt(&ok, 16);
    if(ok)
    {
        decEdit->setText(QString::number(num));
        binEdit->setText(QString::number(num, 2));
    }
    else {
        decEdit->setText("");
        binEdit->setText("");
    }
}

void ByteConverterDialog::binChanged(const QString & newValue)
{
    bool ok;
    int num = newValue.toInt(&ok, 2);
    if(ok)
    {
        hexEdit->setText(QString::number(num, 16));
        decEdit->setText(QString::number(num));
    }
    else
    {
        hexEdit->setText("");
        decEdit->setText("");
    }
}
