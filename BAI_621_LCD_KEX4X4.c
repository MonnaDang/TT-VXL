
#include<tv_boards.c> 
#include<tv_lcd.c>
#include<tv_key4x4.c>

void main()
{
   system_init();
   lcd_setup();
   lcd_goto(3,0);
   lcd_data("HAY NHAN PHIM");

   while(true)
   {
      if(key4x4_read() == OK)
      {
         lcd_goto(19,1);
         if(key4x4.key < 10)lcd_data(key4x4.key + 0x30);
         else lcd_data(key4x4.key  + 0x37); // xem bang ascii 
      }
   }
}

