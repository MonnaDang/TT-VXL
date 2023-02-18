
#include <tv_boards.c>

unsigned int8 T0,T0_temp = 255;
int1 tt;

void check_input(){
   if(!inputcd(UP)){
      tt = !tt;
      if(tt) setup_timer_0(t0_off);
      else setup_timer_0(t0_ext_h_to_l|t0_div_1);
   }
   if(!inputcd(DW)){
      T0 = 0;
      set_timer0(0);
   }
}

void main(){
   system_init();
   
   setup_timer_0(t0_ext_h_to_l|t0_div_1);
   set_timer0(0);
   
   while(true){
      check_input();
      T0 = get_timer0();
      if(T0 != T0_temp){
         T0_temp = T0;
         s7seg.led[0] = m7d[T0%10];
         s7seg.led[1] = m7d[T0/10];
      }
      s7seg_display();
   }
}
