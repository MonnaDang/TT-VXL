

#define BOARD D501

#include<tv_boards.c> 

unsigned int8 dem=0;

void main()
{
   system_init();

   while(true)
   {
      do{
         d7seg.led[0] = m7d[dem%10];
         d7seg.led[1] = m7d[dem/10%10];
         d7seg_display();
         delay_ms(100);
         dem++;
      }while(dem<60);
      delay_ms(3000);
      dem = 59;
      do{
         d7seg.led[0] = m7d[dem%10];
         d7seg.led[1] = m7d[dem/10%10];
         d7seg_display();
         delay_ms(100);
         dem--;
      }while(dem!=0xff);
      delay_ms(3000);
   }
}




