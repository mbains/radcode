#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>


#define BUF_SIZE 1024


int utils_stol(char * str, long * val)
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

//struct moni_info{
//    int chan_val,
//    int rs_val,
//    int dBm_val,
//    int PWR_val,
//    int RXLev_val
//}Moni_info;

enum info {
    chann = 0,
    rs,
    dBm,
    MCC,
    MNC,
    LAC,
    cell, 
    NCC,
    BCC, 
    PWR,
    RXLev,
    C1,
    info_end
};


int main(int argc, char *argv[])
{
    char buffer[BUF_SIZE + 1] = {'\0'};
    int fd = open("./sample_file", O_RDONLY);
    int bytes_read = 0;
    if((bytes_read = read(fd, buffer, BUF_SIZE))){
        char *token = strtok(buffer, " \t");
        int i = 0;
        printf("cnt  token\n");
        printf("==========\n");
        int start_values = -1;
        while (token) {
            printf("%2d %s\n", i++, token);
            if(!strncmp(token, "ChMod", 5)){
                char * ptr = token + 5;
                while(*ptr != '\0' && *ptr == '\n'){
                    ptr++;
                }
                printf("Chan = %s\n", ptr);
                start_values = 0;
                
            }
            
            if( (start_values >= 0) && (start_values < info_end)){
                
                long value = 0;
                if(utils_stol(token, &value) == 0){
                    switch(start_values){
                        case rs:
                            printf("rs %ld\n", value);
                            break;
                        case dBm:
                            printf("dBm %ld\n", value);
                            break;
                        case PWR:
                            printf("PWR %ld\n", value);
                            break;
                        case RXLev:
                            printf("RXLev %ld\n", value);
                            break;
                        default:
                            break;
                    }
                    
                }
                start_values++;
            }
            
            token = strtok(NULL, " \t");
        }
    }
    return 0;
}