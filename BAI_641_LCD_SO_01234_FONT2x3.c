
#include<tv_boards.c> 
#include<tv_lcd.c>

void main()
{
   system_init();
   lcd_setup();
   lcd_write_2x3_num(0,0,1); // Hi?n th? s? 0 ? hàng 1 c?t 0
   lcd_write_2x3_num(1,4,1); // Hi?n th? s? 1 ? hàng 1 c?t 4
   lcd_write_2x3_num(2,8,1); // Hi?n th? s? 2 ? hàng 1 c?t 8
   lcd_write_2x3_num(3,12,1); // Hi?n th? s? 3 ? hàng 1 c?t 12
   lcd_write_2x3_num(4,16,1); // Hi?n th? s? 4 ? hàng 1 c?t 16
   while(true)
   {
   }
}

