#define BOARD D501
#include<tv_boards.c>
#include<tv_lcd.c>

unsigned int8 giay=0;

void main()
{
   system_init();
   lcd_setup();
   lcd_goto(0,0);
   lcd_data("HIEN THI BIEN GIAY");

   while(true)
   {
      lcd_goto(9,3);
      lcd_data(giay / 10 % 10 + 0x30);
      lcd_data(giay % 10 + 0x30);
      giay++;
      giay %= 60;
      delay_ms(1000);
   }
}

