
#include<tv_boards.c> 
unsigned int8 T0,T0_TAM=0xff; 

void d7seg_xoa0VN(unsigned int16 d)
{
   unsigned int8 n = 0;

   do
   {
      d7seg.led[n] = m7d[d % 10];
      d /= 10; n++;
   }while(d != 0);

   for(; n < 4; n++)d7seg.led[n] = 0xff;
   d7seg_display();
}

void main()
{
   system_init();
   setup_timer_0(T0_EXT_H_TO_L|T0_DIV_1);
   set_timer0(0);

   while(true)
   {
      T0 = get_timer0();
      if(T0 > 100)set_timer0(1);

      if(T0 != T0_TAM)
      {
         T0_TAM = T0;
         d7seg_xoa0VN(T0);
      }
   }
}

