
#include <tv_boards.c>
#include <tv_lcd.c>

unsigned int8 T0=0,T0_temp=255;

void giai_ma7d(unsigned int8 x){
   unsigned int _i=0;
   do{
      d7seg.led[_i] = m7d[x%10];
      s7seg.led[_i] = m7d[x%10];
      x /= 10;
      _i++;
   }while(_i<3);
}

void main(){
   system_init();
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(98);
   
   lcd_setup();
   
   while(true){
      T0 = get_timer0();
      if(T0 > 100){
         T0 = T0 - 100;
         set_timer0(T0);
      }
      if(T0 != T0_temp){
         T0_temp = T0;
         giai_ma7d(T0);
         d7seg_display();
//!         lcd_goto(9,0);
         lcd_write_2x3_num(T0/100,4,0);
         lcd_write_2x3_num(T0/10%10,7,0);
         lcd_write_2x3_num(T0%10,10,0);
      }
      s7seg_display();
   }
}

