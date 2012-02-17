#ifndef CLASS_H
#define CLASS_H

#include "Python.h"
#include "arrayobject.h"

class klass{
public:
    klass();
    ~klass();
    int arraySum(double  array[4]);
    int add(int x, int y);
    PyArrayObject *trace( PyObject *args);


private:
    int value_a;
    int value_b;
};

#endif

