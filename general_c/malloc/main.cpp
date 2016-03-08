#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEGABYTE 1024*1024

int main(int argc, char *argv[])
{
        void *myblock = NULL;
        int count = 0;
        char c;
        while(1)
        {
                myblock = (void *) malloc(MEGABYTE);
                if (!myblock) break;
                memset(myblock,1, MEGABYTE);
                printf("Currently allocating %d MB\n",++count);
                if( (count % 2000) == 0) {
                    printf("read more? \n");
                    scanf("%c", &c);
                }
        }
        exit(0);
        
}
