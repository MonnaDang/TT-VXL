

#include<tv_boards.c> 
#include<tv_lcd.c> 

const unsigned int8 cotsong[]=
{
   0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,
   0x00,0x00,0x00,0x00,0x08,0x08,0x18,0x18,
   0x00,0x00,0x04,0x04,0x0C,0x0C,0x1C,0x1C,
   0x00,0x02,0x06,0x06,0x0E,0x0E,0x1E,0x1E,
   0x01,0x03,0x07,0x07,0x0F,0x0F,0x1F,0x1F
};

unsigned int8 n;

void main()
{
   system_init();
   lcd_setup();
   lcd_command(0x40);
   for(n = 0; n < 40; n++)lcd_data(cotsong[n]);
   while(true)
   {
      for(n = 0; n < 5; n++)
      {
         lcd_goto(18,0);
         lcd_data(n); 
         delay_ms(200);
      }
   }
}
