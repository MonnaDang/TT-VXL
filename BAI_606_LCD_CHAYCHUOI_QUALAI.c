
#define BOARD D501
#include<tv_boards.c> 
#include<tv_lcd.c>

signed int8 giay=0,n;
char chuoi[] = "TRUONG DAI HOC SU PHAM KY THUAT TP.HCM";
char dlht[20] = "                    ";
int1 tt=0;

unsigned int8 i=0,j=0,chay=0;

signed int8 chieu=1;

void chay_chuoi(){
   if(!tt){
      for(i=0;i<19;i++){
         dlht[i] = dlht[i+1];
      }
      dlht[19] = chuoi[chay]; 
      if(chay == 37) {
         chay = 17;          // con tro tra ve lai vi tri " "truoc chu PHAM de dich phai
         tt = !tt;
      }
      else chay++;           // tang de dich trai
   }else{
      for(i=19;i>0;i--){
         dlht[i] = dlht[i-1];
      }
      dlht[0] = chuoi[chay];  // gan lai cac ky tu truoc chu PHAM 
      if(chay == 0) {
         chay = 20;           // con tro tra ve lai vi tri AM de chuoi hien thi lien tuc
         tt = !tt;
      }
      else chay--;            // giam de dich phai
   }
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
   lcd_goto(0,0);
   for(i=0;i<20;i++) lcd_data(' ');
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
//!      for(j=0;j<20;j++){
//!         lcd_data(dlht[j]);
//!      }
      printf(lcd_data,"%s",dlht);
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

