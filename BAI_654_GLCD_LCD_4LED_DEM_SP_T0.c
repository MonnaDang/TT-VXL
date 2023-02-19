
#include <tv_boards.c>
#include <tv_glcd.c>
#include <tv_lcd.c>

unsigned int8 T0,T0_temp=24;

void ht_lcd(){
   lcd_goto(0,0);
   printf(lcd_data,"%2u",T0);
   lcd_write_2x3_num(T0/10,3,0);
   lcd_write_2x3_num(T0%10,6,0);
   lcd_write_4x3_num(T0/10,10);
   lcd_write_4x3_num(T0%10,13);
}

void ht_glcd(){
   //font 1
   glcd_text_setup(0,0,1,1,1);
   printf(glcd_text,"%2u",T0);
   glcd_update();
   //font 2
   glcd_text_setup(15,0,2,1,1);
   printf(glcd_text,"%2u",T0);
   glcd_update();
   //font 3
   glcd_text_setup(40,0,3,1,1);
   printf(glcd_text,"%2u",T0);
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
 
   while(true){
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
