#include <iostream>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdint.h>
using namespace std;


int main(int argc, char ** argv)
{
   struct bitfield
   {
      unsigned bits3 : 3;
      unsigned bits1 : 1;
      unsigned bits4 : 4;
      uint16_t lots  : 16;
   }__attribute__((__packed__));

   struct testfield {
       unsigned short field1;
       unsigned short field2;
       unsigned short field3;
   };

   bitfield myfield;
   memset(&myfield, 0, sizeof(myfield));
   uint16_t littleEnd = 0xfeed;
   uint16_t bigEnd = htons(0xfeed);
   myfield.bits3 = 0x5;
   myfield.bits1 = 1;
   myfield.bits4 = 0xa;
   myfield.lots  = (0xffaa);

   struct testfield myfield2;
   myfield2.field1 = 4;
   myfield2.field2 = 20;
   myfield2.field3 = 82;
   unsigned short * fp = (unsigned short *)&myfield2;

    
   for(int i = 0; i < sizeof(myfield2); i++) {
        printf("0x%04hx\n", fp[i]);
   }
   return 0;
}

