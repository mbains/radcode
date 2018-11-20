#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#define MEGABYTE 1024*1024

int main(int argc, char *argv[])
{

    FILE * output = popen("/bin/ping -c 5 8.8.8.8", "w");
    pclose(output);    

    printf("output = %d\n", WEXITSTATUS(output));	
    //printf
        
}
