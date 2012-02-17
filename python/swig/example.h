#ifndef CLASS_H
#define CLASS_H

#include "Python.h"
#include "Numeric/arrayobject.h"

class klass{
public:
    klass(int value);
    ~klass();

};

static int insta;
static klass klasses[4] = {klass(++insta), klass(++insta), klass(++insta), klass(++insta)};
#endif
