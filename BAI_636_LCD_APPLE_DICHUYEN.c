
#include<tv_boards.c> 
#include<tv_lcd.c> 

const unsigned int8 traitao[]=
{
   0x00,0x00,0x00,0x07,0x0F,0x0F,0x1F,0x1F,     
   0x07,0x0E,0x10,0x1C,0x1E,0x1E,0x1F,0x1F,
   0x1F,0x1F,0x0F,0x07,0x03,0x00,0x00,0x00,
   0x1F,0x1F,0x1E,0x1C,0x18,0x00,0x00,0x00
};

unsigned int8 n;

void main()
{
   system_init();
   lcd_setup();
   lcd_command(0x40);
   for(n = 0; n < 32; n++)lcd_data(traitao[n]);
   lcd_goto(0,0);
   lcd_data(" BIEU TUONG APPLE ");
   while(true)
   {
      for(n = 0; n < 19;n++){
         lcd_goto(n,1);
         lcd_data(0); lcd_data(1);
         lcd_goto(n,2);
         lcd_data(2); lcd_data(3);
         delay_ms(500);
         lcd_goto(n,1);
         lcd_data(0x20); lcd_data(0x20);
         lcd_goto(n,2);
         lcd_data(0x20); lcd_data(0x20);
      }
      for(n = 19; n >= 1;n--){
         lcd_goto(n-1,1);
         lcd_data(0); lcd_data(1);
         lcd_goto(n-1,2);
         lcd_data(2); lcd_data(3);
         delay_ms(500);
         lcd_goto(n-1,1);
         lcd_data(0x20); lcd_data(0x20);
         lcd_goto(n-1,2);
         lcd_data(0x20); lcd_data(0x20);
      }
   }
}

