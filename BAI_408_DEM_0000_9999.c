#define BOARD D501

#include<tv_boards.c> 

unsigned int16 dem;

void main()
{
   system_init();

   while(true)
   {
      for(dem = 0; dem<10000 ; dem++){
         d7seg.led[0] = m7d[dem%10];
         d7seg.led[1] = m7d[dem/10%10];
         d7seg.led[2] = m7d[dem/100%10];
         d7seg.led[3] = m7d[dem/1000%10];
         d7seg_display();
         delay_ms(50);
      }
   }
}
