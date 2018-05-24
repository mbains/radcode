#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>


#define BUF_SIZE 256


int parse_main(char * str, long * val)
{
   char *endptr;

   errno = 0;    /* To distinguish success/failure after call */
   *val = strtol(str, &endptr, 10);

   /* Check for various possible errors */

   if ((errno == ERANGE && (*val == LONG_MAX || *val == LONG_MIN))
           || (errno != 0 && *val == 0)) {
       perror("strtol");
       return -1;
   }

   if (endptr == str) {
       //fprintf(stderr, "No digits were found\n");
       return -2;
   }

   /* If we got here, strtol() successfully parsed a number */
   //printf("strtol() returned %ld\n", *val);

   if (*endptr != '\0')        /* Not necessarily an error... */
   {
       //printf("Further characters after number: %s\n", endptr);
       return -3;
   }

   return 0;
}


int main(int argc, char *argv[]) {

    char buf [BUF_SIZE + 1] = {'\0'};
    //int fd = open("./sample_file", O_RDONLY);
    FILE *file_p = fopen("./sample_file", "r");
    
    fscanf(file_p, "%s", buf);
    printf("%s\n", buf);
    
    fscanf(file_p, "%s", buf);
    printf("%s\n", buf);
 
    while((fscanf(file_p, "%s", buf) != EOF)) {
       
        printf("%s -- ", buf);
        long test_val;
        if(parse_main(buf, &test_val) == 0) {
            printf("Got value %ld", test_val);
        }
        printf("\n");
    }
    
    fclose(file_p);

}
