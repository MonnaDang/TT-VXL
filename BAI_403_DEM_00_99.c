
#define BOARD D501

#include<tv_boards.c> 
unsigned int8 dem;

void main()
{
   system_init();

   while(true)
   {
      for(dem = 0; dem < 100; dem++)
      {
         d7seg.led[0] = m7d[dem%10];
         d7seg.led[1] = m7d[dem/10%10];
         d7seg_display();
         delay_ms(500);
      }
   }
}

