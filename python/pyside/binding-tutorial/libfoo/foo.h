#ifndef FOO_H
#define FOO_H

#include <QtCore/QtCore>

class Math : public QObject
{
    Q_OBJECT
public:
    Math() {}
    virtual ~Math() {}
    int squared(int x);
};

#endif // FOO_H

