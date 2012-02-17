#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>
#include <string.h> 
using namespace std;
#define ARRAY_SIZE(x) sizeof(x)/sizeof(*x)

class FooBar 
{  
public:
   char buf[500];
   FooBar()
   {
      printf("constructor called, address of buf = 0x%08x \n", (unsigned int) buf);
   }
   ~FooBar()
   {
      printf("destructor called\n");
   }
   FooBar(const FooBar& orig)
   {
      printf("copy constructor called, 0x%08x, address of buf = 0x%08x \n", (unsigned int)&orig, (unsigned int) buf);
   }
};

int var = 0;
bool varLessThan5()
{
   var ++;
   if (var >= 5)
      return false;

   return true;
}

const char * chararrays[] = {"one", "two", "three", NULL};

const char * getMoreChars(int idx)
{
   return chararrays[idx];
}

#define SAFE_DELETE(ptr) if(ptr) delete ptr; ptr = NULL;
int main(int argc, char ** argv)
{
    int * ints = new int[5]; //pointer pointing to a contigeous piece of allocated ints
    int * integer = new int(5);
    int * ints1[2]; //array of pointers

   bool status = false;
   while(status = varLessThan5())
   {
      cout << "still less than 5 " << var << endl;
   }

   int currIdx = 0;
   const char * readA = NULL;
   while(readA = getMoreChars(currIdx++))
   {
      cout << "Got chars: " << readA << endl;
   }

    FooBar bar = FooBar();
    //FooBar foo(bar);
    printf("value of uninitialized buffer inside statically allocated instance: [%s]\n", bar.buf);

    char someStrings[5][4]= {"jo", "ho", "doe", "foe", "moe"};
    printf("size of someStrings:%d\n", sizeof(someStrings));

    ints1[0] = new int(10);
    ints1[1] = new int(20);
   
    ints[0] = 42;
    printf("normal %d\n", ints[0]);
    SAFE_DELETE(integer); //demo safe delete
    SAFE_DELETE(integer);
    SAFE_DELETE(integer);
    sleep(2);
    //printf("fence post %d\n", ints[6]);
    sleep(3);
    delete [] ints; //delete group
    printf("after delete %d\n", ints[0]);
    sleep(3);
    printf("writing to freed memory\n");
    ints[1]=30;
    delete ints1[0]; //have to delete seperately
    delete ints1[1];
    return 0;
}

