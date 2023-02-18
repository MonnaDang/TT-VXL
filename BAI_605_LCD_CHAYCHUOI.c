
#define BOARD D501
#include<tv_boards.c> 
#include<tv_lcd.c>

signed int8 giay=0,n;
char chuoi[] = "TRUONG DAI HOC SU PHAM KY THUAT TP.HCM";
char dlht[20] = " ";

unsigned int8 i=0,j=0,chay=0;

signed int8 chieu=1; 

void chay_chuoi(){
   for(i=0;i<19;i++){
      dlht[i] = dlht[i+1];
   }
   if(chay<38) dlht[19] = chuoi[chay]; 
   else dlht[19] = 0x20;
   if(chay == 38) chay = 0;
   else chay++;
}

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
//!   lcd_goto(0,0);
//!   lcd_data("BAI TAP CHINH MENU");
   lcd_goto(1,1);
   lcd_data("DEM LEN");
   lcd_goto(1,2);
   lcd_data("DEM XUONG");
   hienthi_muiten();

   while(true)
   {  
      chay_chuoi();
      lcd_goto(0,0);
      for(j=0;j<20;j++){
         lcd_data(dlht[j]);
      }
      lcd_goto(9,3);
      printf(lcd_data,"%2u",giay);
      giay = giay + chieu;
      if(giay >= 60)giay = 0;
      else if(giay < 0)giay = 59;
      for(n = 0; n < 100; n++)
      {
         kiemtra_inv();
         delay_ms(5);
      }
   }
}

