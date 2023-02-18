
#define BOARD D501
#include <tv_boards.c>

unsigned int8 T0,T0_temp=255;

void check_input(){
   if(!input(ON)){
      setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
      led32.ledx32 = ~((int32)0);
      led32_display();
   }
   if(!input(OFF)){
      setup_timer_0(T0_OFF);
      led32.ledx32 = 0;
      led32_display();
   }
}

void d7seg_xoa0VN(unsigned int16 d){
   unsigned int8 m=0;
   do{
      d7seg.led[m] = m7d[d%10]; // hang don vi -> hang ngan 
      d/=10;                    // 
      m++;                      // vi do while nen m luon luon tang 1, ko xoa hang don vi
   }while(d!=0);  // hang nay xoa 0 vn (d!=0)
   for(;m<4;m++)d7seg.led[m] = 0xff; 
   d7seg_display();
}




void main(){
   
   setup_timer_0(t0_ext_h_to_l|t0_div_1);
   set_timer0(98);
   
   system_init();
   
   led32.ledx32 = ~((int32)0);
   led32_display();
   
   while(true){
      check_input();
      T0 = get_timer0();
      if(T0 > 100){
         
         T0 = T0 - 100;
         set_timer0(T0);
      }
      if(T0 != T0_temp){
         T0_temp = T0;
         d7seg_xoa0VN(T0);
      }
   }
}
