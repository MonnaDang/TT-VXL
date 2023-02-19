
#include<tv_boards.c> 
#include<tv_lcd.c>

const unsigned int8 traitim[]={0x0a,0x15,0x11,0x11,0x0a,0x04,0,0};

unsigned int8 n;

void main()
{
   system_init();
   lcd_setup();
   lcd_command(0x40); 
   for(n = 0; n < 8; n++)lcd_data(traitim[n]); 
   lcd_goto(0,1);
   for(int i=0;i<20;i++)lcd_data(0);
   while(true)
   {
   }
}

