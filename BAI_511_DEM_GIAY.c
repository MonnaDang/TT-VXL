#define BOARD D501
#include<tv_boards.c> 
unsigned int8 giay,i;

void main()
{
   system_init();

   while(true)
   {
      for(giay = 0; giay < 60; giay++)
      {
         s7seg.led[1] = m7d[giay / 10 % 10];
         s7seg.led[0] = m7d[giay % 10];
         for(i = 0; i < 50; i++)s7seg_display(); // delay – hi?n th?
      }
   }
}

