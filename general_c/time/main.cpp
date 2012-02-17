#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

using namespace std;

int main(int argc, char ** argv)
{
    struct timeval t1;
    time_t t;
    double time_d;

    uint32_t someNumber = 2717992;
    printf("someNumber = 0x%08lx\n", someNumber);
    for(int i = 0; i < 100; i++)
    {
        time(&t);
        (void)gettimeofday(&t1, NULL);
        printf(" \033[0;31m time: %d \033[m\n", (uint32_t)t);
        time_d = t1.tv_sec + t1.tv_usec * 1E-6;
        printf("gettimeofday %f\n", time_d);
    }
    return 0;
}

