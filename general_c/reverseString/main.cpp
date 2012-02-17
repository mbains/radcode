#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

using namespace std;

char * reverse(char *str)
{
    int strSize = 1;
    char * ptr1 = str;
    char * ptr2 = str;
    bool notDone = true;
    bool startedWord = false;
    for(char * tmp = str; *tmp != '\0'; tmp++)
    {
        strSize++;
    }
    char * generatedString = new char[strSize];
    int currIdx = 0;
    int copiedIdx = 0;
    while(notDone){
        if(*ptr1 == '\0')
            notDone = false;


        if(*ptr1 != ' ')

        {
            if(startedWord == false){
                //cout << "started word" << endl;
                startedWord = true;
                ptr2 = ptr1;
            }
        }

        if(startedWord && (*ptr1 == ' ' || *ptr1 == '\0')){
            for(char * tmpPtr = ptr1 - 1; tmpPtr >= ptr2; tmpPtr--)
            {
                //cout << "copying " << char(*tmpPtr);
                generatedString[copiedIdx++] = *tmpPtr;
            }
            startedWord = false;
        }
        if(*ptr1 == ' ')
            generatedString[copiedIdx++] = *ptr1;

        ptr1++;
        currIdx++;
    }
    return generatedString;
}

void ptrTest()
{
    int intarray[5] = {1,2,3,4,5};
    int * intptr = intarray;
    printf("address pointed = 0x%08x\n", (unsigned int) intptr);
    for(int i = 0; i < 5; i++)
    {
        printf("i = %d, address pointed = 0x%08x, value = %d\n", i, (unsigned int) intptr, *intptr);
        intptr++;
    }
    printf("size of int %d, size of int * %d", sizeof(*intptr), sizeof(intptr));
}

int main(int argc, char ** argv)
{
    char dataS[20] = "This is a string";

    cout << reverse(dataS) << endl;
    return 0;
}





