#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

union Data {
    float f;
    uint32_t i;
    uint16_t h[2];
};


int main(int argc, char **argv) {

    Data d;
    d.f = 5.4;
    printf("5.4f as uInt = %u\n", d.i); 
    printf("5.4f as hW = %u, %u\n", d.h[0], d.h[1]); 
    return 0;
}
