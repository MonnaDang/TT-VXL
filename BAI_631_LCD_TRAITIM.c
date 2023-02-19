
#include<tv_boards.c> 
#include<tv_lcd.c>

const unsigned int8 traitim[]={0x0a,0x15,0x11,0x11,0x0a,0x04,0,0};

unsigned int8 n;

void main()
{
   system_init();
   lcd_setup();
   lcd_command(0x40); // Di chuy?n d?n vùng nh? CGRAM
   for(n = 0; n < 8; n++)lcd_data(traitim[n]); // Ghi mã trái tim vào CGRAM
   lcd_goto(0,0);
   lcd_data(0); //Hi?n th? trái tim
   while(true)
   {
   }
}

