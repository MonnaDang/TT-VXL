
#include <tv_boards.c>
#include <tv_glcd.c>

unsigned int16 T0,T0_temp=999;

void ve_hinh(unsigned int8 dem){
   glcd_clear(0);
   
   unsigned int _i=0;
   while(dem != 0){
      glcd_bar(9-_i*4,10,9-_i*4,10-dem%10,3,dem%10 != 0);
      dem /= 10;
      _i++;
   }
   glcd_update();
}

void main(){
   system_init();
   
   glcd_setup();
   
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(0);
   
   while(true){
      T0 = get_timer0();
      if(T0 > 999){
         T0 = T0 - 999;
         set_timer0(T0);
      }  
      if(T0 != T0_temp){
         T0_temp = T0;
         ve_hinh(T0);
      }
   }
}
