#define BOARD D501
#include<tv_boards.c> 
#include<tv_lcd.c>

signed int8 giay=0,n; 

signed int8 chieu=1; 
void hienthi_muiten()
{
   if(chieu == 1)
   {
      lcd_goto(0,1);
      lcd_data(0x7e);
      lcd_goto(0,2);
      lcd_data(" ");
   }

   else
   {
      lcd_goto(0,1);
      lcd_data(" ");
      lcd_goto(0,2);
      lcd_data(0x7e);
   }
}

void kiemtra_inv()
{
   if(inputcd(INV) == 0)
   {
      chieu = - chieu;
      hienthi_muiten();
   }
}

void main()
{
   system_init();
   lcd_setup();
   lcd_goto(0,0);
   lcd_data("BAI TAP CHINH MENU");
   lcd_goto(1,1);
   lcd_data("DEM LEN");
   lcd_goto(1,2);
   lcd_data("DEM XUONG");
   hienthi_muiten();

   while(true)
   {
      lcd_goto(9,3);
      printf(lcd_data,"%2u",giay);
      giay = giay + chieu;
      if(giay >= 60)giay = 0;
      else if(giay < 0)giay = 59;
      for(n = 0; n < 100; n++)
      {
         kiemtra_inv();
         delay_ms(10);
      }
   }
}

