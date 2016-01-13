#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "ring.h"

int main(int argc, char **argv) {
    RingBuffer buf = {0, 0};
    Enqueue(&buf, 1);
    Enqueue(&buf, 2);
    Enqueue(&buf, 3);
    Enqueue(&buf, 4);
    Enqueue(&buf, 5);

    uint8_t d;
    Dequeue(&buf, &d);
    Dequeue(&buf, &d);
    Dequeue(&buf, &d);
    Dequeue(&buf, &d);
    
    return 0;
}
