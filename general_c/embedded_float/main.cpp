#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

static char str[30];
void float_to_str(float val, char * buf) {
    int d1 = val;            // Get the integer part (678).
    float f2 = val - d1;     // Get fractional part (0.01234567).
    int d2 = trunc(f2 * 10000);   // Turn into integer (123).
    float f3 = f2 * 10000 - d2;   // Get next fractional part (0.4567).
    int d3 = trunc(f3 * 10000);   // Turn into integer (4567).
    
    sprintf (buf, "%d.%04d%04d", d1, d2, d3);
}

void double_to_str(double val, char * buf) {
    long d1 = val;            // Get the integer part (678).
    float f2 = val - d1;     // Get fractional part (0.01234567).
    int d2 = trunc(f2 * 10000);   // Turn into integer (123).
    float f3 = f2 * 10000 - d2;   // Get next fractional part (0.4567).
    int d3 = trunc(f3 * 10000);   // Turn into integer (4567).
    
    sprintf (buf, "%ld.%04d%04d", d1, d2, d3);
}

void test_float_to_str() {
    int divisor = 0;
    int d_mod = 0;
    float answer = 0;
    while(1) {
        d_mod = divisor % 10000;
        printf("1/%u = ", d_mod);
        if( d_mod) {
            answer = 1./d_mod;
        } else {
            answer = 0;
        }
        float_to_str(answer, str);
        printf("<%20s>\r\n", str);
        divisor++;
        if(divisor >1000) {
            break;
        }
        sleep(0.1);
    }
}

void test_large_to_str() {

    int mult = 1;
    float initial, i_large = 8342333;
    initial=i_large;
    //i_large = 30;
    while(mult < 25) {

        i_large += (initial);
        mult++;
        float_to_str(i_large, str);
        printf(" * %d ", mult);
        printf("answer = <%30s>\r\n", str);
        sleep(0.1);
    }

}


int main(int argc, char **argv) {

    test_large_to_str(); 
    return 0;
}
