#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MEGABYTE 1024*1024

int main(int argc, char *argv[]) {

    //an array has the size built in at compile time
    char cmd[][80] = {"test", "foo", "end"};
    printf("sizeof = %ld \n", sizeof (cmd) / sizeof (cmd[0]));

    //array of pointers does not
    const char * cmd_ptr[] = {"test", "foo", "end", NULL};
    //we iterate a pointer
    const char ** tmp_ptr = cmd_ptr;
    while (*tmp_ptr) {
        tmp_ptr++;
    }

    printf("size from ptr = %ld\n", (tmp_ptr - cmd_ptr));

}
