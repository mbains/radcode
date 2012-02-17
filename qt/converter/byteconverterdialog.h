#ifndef BYTECONVERTERDIALOG_H
#define BYTECONVERTERDIALOG_H

#include <QDialog>
class QLineEdit;

class ByteConverterDialog: public QDialog
{
    Q_OBJECT

    public:
        ByteConverterDialog();
    private:
        QLineEdit * decEdit;
        QLineEdit * hexEdit;
        QLineEdit * binEdit;

    private slots:
        void decChanged(const QString&);
        void hexChanged(const QString&);
        void binChanged(const QString&);
};

#endif
