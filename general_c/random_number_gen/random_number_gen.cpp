#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

int main(int argc, char ** argv)
{
    srandom(35);
    int i = 0;
    long r = 0;
    float result = 0;

    while(i < 10000)
    {
        r = random();
        result = double(r)/RAND_MAX;
        if(result > 0.999 || result < 0.001)
            printf("i=%d, random = %f\n", i, double(r)/RAND_MAX);
        i++;
    }
    return 0;
}

