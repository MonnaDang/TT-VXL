
#define BOARD D501
#include <tv_boards.c>

unsigned int16 T0=9997;

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
   set_timer0(9997);
   
   system_init();
   d7seg_xoa0VN(T0);
   
   while(true){
      T0 = get_timer0();
      if(T0 > 9999){
         
         T0 = T0 - 9999;
         set_timer0(T0);
      }
      d7seg_xoa0VN(T0);
   }
}
