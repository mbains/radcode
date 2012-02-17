#include "example.h"
#include "Python.h"
#include "arrayobject.h"

#include <stdio.h>
#define PY_ARRAY_UNIQUE_SYMBOL
klass::klass()
{
	printf("constructor called\n");
        import_array();
}
klass::~klass()
{
	printf("destructor called\n");
}

 PyArrayObject * klass::trace( PyObject *args)
{

    PyArrayObject *array = (PyArrayObject *) args;

    double sum;

    int i, n;


    //printf("got %d but expected %d\n", array->descr->type_num, int(PyArray_DOUBLE));
    if (array->nd != 2 /* || array->descr->type_num != PyArray_DOUBLE*/)
    {
        PyErr_SetString(PyExc_ValueError, "array must be two-dimensional and of type float");

        return NULL;
    }



    n = array->dimensions[0];

    if (n > array->dimensions[1])
        n = array->dimensions[1];

    sum = 0.;

    for (i = 0; i < n; i++)
        sum += *(double *)(array->data + i*array->strides[0] + i*array->strides[1]);

    return array;
}

int klass::add(int x, int y)
{
     return x + y;
}

int klass::arraySum(double array[4])
{
   int sum = 0;
   for(int i = 0; i < 4; i++)
   {
      printf("%f\n", array[i]);
      sum = array[i] + sum;
   }
   return sum;
}



