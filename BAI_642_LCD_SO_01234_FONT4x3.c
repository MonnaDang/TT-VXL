#include<tv_boards.c> 
#include<tv_lcd.c>

void main()
{
   system_init();
   lcd_setup();
   lcd_write_4x3_num(0,0);
   lcd_write_4x3_num(1,3);
   lcd_write_4x3_num(2,6);
   lcd_write_4x3_num(3,9);
   lcd_write_4x3_num(4,12);
   while(true)
   {
   }
}

