#include <iostream>
#include <stdio.h>
using namespace std;

#define PCT_CAP(x) (x>100?100:(x<0? 0: x))


typedef enum Enum_e
{
   Type1 = 0,
   Type2,
   Type3
} EnumT;

#define GET_TYPE(type) \
 type==Type1 ? "Type1" : (type==Type2) ? "Type2":\
  (type == Type3) ? "Type3": "Unknown" \


int main(int argc, char ** argv)
{

   float pct = 102;
   float pct2 = 99;
   float pct3 = -1;
   printf("%f, %f, %f, %f, %f, %f\n", PCT_CAP(-1.), PCT_CAP(0.0), PCT_CAP(1.), PCT_CAP(99.0), PCT_CAP(100.0), PCT_CAP(101.0));
   printf("type of Type1 = %s\n", GET_TYPE(Type1)); 
   printf("type of Type2 = %s\n", GET_TYPE(Type2)); 
   printf("type of Type3 = %s\n", GET_TYPE(Type3));
   printf("type of 4(not defined) = %s\n", GET_TYPE(4));
   return 0;
}

