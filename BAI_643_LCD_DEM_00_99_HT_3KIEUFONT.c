
#include<tv_boards.c> 
#include<tv_lcd.c>

unsigned int8 dem=0;

void main()
{
   system_init();
   lcd_setup();

   while(true)
   {
      for(dem = 0; dem < 100; dem++)
      {
         lcd_goto(0,2);
         printf(lcd_data,"%02u",dem); // Font 1x1
         lcd_write_2x3_num(dem / 10 % 10,6,1); // Hàng ch?c Font 2x3
         lcd_write_2x3_num(dem % 10,9,1); // Hàng don v? Font 2x3
         lcd_write_4x3_num(dem / 10 % 10,14); // Hàng ch?c font 4x3
         lcd_write_4x3_num(dem % 10,17); // Hàng don v? font 4x3
         delay_ms(300);
      }
   }
}

