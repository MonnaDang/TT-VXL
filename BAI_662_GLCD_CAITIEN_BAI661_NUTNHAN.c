
#include <tv_boards.c>
#include <tv_glcd.c>
#include <tv_lcd.c>

unsigned int8 T0,T0_temp=24;
int1 tt=0;

void hinh_thoi(int1 mau){
   glcd_bar(85,1,130,1,1,mau);
   glcd_bar(85,1,70,61,1,mau);
   glcd_bar(70,61,115,61,1,mau);
   glcd_bar(115,61,130,1,1,mau);
}

void kt_nt(){
   if(!inputcd(INV)){
      tt = !tt;
      if(!tt){
         hinh_thoi(0);
         glcd_circle(100,31,30,0,1);
         glcd_update();
      }else{
         glcd_circle(100,31,30,0,0);
         hinh_thoi(1);
         glcd_update();
      }
   }  
}

void ht_lcd(){
   lcd_goto(0,0);
   printf(lcd_data,"%2u",T0);
   lcd_write_2x3_num(T0/10,3,0);
   lcd_write_2x3_num(T0%10,6,0);
   lcd_write_4x3_num(T0/10,10);
   lcd_write_4x3_num(T0%10,13);
}

void ht_glcd(){
   glcd_text_setup(95,28,1,1,1); // Y = lay Tam - y_font/2 ; X = tam - (sochu*x_font)/2
   printf(glcd_text,"%02u",T0);
   glcd_update();
}

void ht_4led(unsigned int8 sodem){
   unsigned int _i=0;
   do{
      d7seg.led[_i] = m7d[sodem%10];
      sodem /= 10;
      _i++;
   }while(_i<2);
   d7seg_display();
}

void main(){
   system_init();
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(0);
   
   glcd_setup();
   lcd_setup();
   
   glcd_spkt_logo_raw(0);
   glcd_circle(100,31,30,0,1);
   glcd_update();
   
   
   while(true){
      kt_nt();
   
      T0 = get_timer0();
      
      if(T0 > 24){
         T0 = T0 - 24;
         set_timer0(T0);
      }
      
      if(T0 != T0_temp){
         T0_temp = T0;
         ht_lcd();
         ht_glcd();
         ht_4led(T0);
      }
   }
}
