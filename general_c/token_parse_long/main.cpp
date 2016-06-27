
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
 
int main(void)
{
    char input[] = "1 99 42 36";
    printf("Parsing the input string '%s'\n", input);
    char *token = strtok(input, " ");
    while(token) {
        puts(token);
        token = strtok(NULL, " ");
    }
 
    printf("Contents of the input string now: '");
    for(size_t n = 0; n < sizeof input; ++n)
        input[n] ? printf("%c", input[n]) : printf("\\0");
    puts("'");
    printf("\n");

    char szNumbers[] = "2001 60c0c0 -1101110100110100100000 0x6fffff";
    char * pEnd;
    long int li1, li2, li3, li4;
    li1 = strtol(szNumbers, &pEnd, 10);
    li2 = strtol(pEnd, &pEnd, 16);
    li3 = strtol(pEnd, &pEnd, 2);
    li4 = strtol(pEnd, NULL, 0);
    printf("The decimal equivalents are: %ld, %ld, %ld and %ld.\n", li1, li2, li3, li4);
    return 0;
 

}
