#include "example.h"

#include <stdio.h>
#define PY_ARRAY_UNIQUE_SYMBOL
klass::klass(int value)
{
	printf("constructor called, value = %d\n", value);
    import_array();
}
klass::~klass()
{
	printf("destructor called\n");
}


