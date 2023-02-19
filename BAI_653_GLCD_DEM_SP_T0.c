
#include <tv_boards.c>
#include <tv_glcd.c>

unsigned int8 T0,T0_temp=24;

void main(){
   system_init();
   glcd_setup();
   
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(0);
   
   while(true){
      T0 = get_timer0();
      if(T0 > 24){
         T0 = T0 - 24;
         set_timer0(T0);
      }
      if(T0 != T0_temp){
         T0_temp = T0;
         glcd_text_setup(50,10,3,1,1);
         printf(glcd_text,"%2u",T0);
         glcd_update();
      }
   }
}
