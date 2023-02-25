#define BOARD D501
#include <tv_boards.c>

unsigned int16 tong;
unsigned int8 T0=0,T0_temp=99,solan=0,lm35a;
int1 tt = 0;

void kt_nt(){
   static unsigned int16 state;
//!   if(!input(UP)){
   state = (state<<1)|input(UP);
   if(state == 0x8000){
      tt = !tt;
      if(tt) triac_2_on();
      else triac_2_off();
   }
}

void main(){
   system_init();
   
   setup_adc(ADC_CLOCK_DIV_32);
   setup_adc_ports(analog_pins| VSS_VDD);
   set_adc_channel(lm35a_channel);
   
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(0);
   
   while(true){
      tong += read_adc();
      if(solan == 100){
         lm35a = tong/100/2.046;
         solan = 0; tong = 0;
         s7seg.led[0] = m7d[lm35a%10];
         s7seg.led[1] = m7d[lm35a/10];
      }else solan++;
         
//!      lm35a = read_adc()/2.046;
//!      s7seg.led[0] = m7d[lm35a%10];
//!      s7seg.led[1] = m7d[lm35a/10];
      T0 = get_timer0();
      if(T0 > 99){
         T0 = T0 - 99;
         set_timer0(T0);
      }  
      
      if(T0 != T0_temp){
         T0_temp = T0;
         s7seg.led[6] = m7d[T0%10];
         s7seg.led[7] = m7d[T0/10];
      }
      
      s7seg_display();
      kt_nt();
   }
}
