
#define BOARD D501
#include<tv_boards.c> 
unsigned int16 tonga=0;
unsigned int8 n=0,lm35a,gioihan=35;

void check_btn(){
   if(!inputcd(UP)){
      if(gioihan < 60) gioihan++; 
   }
   if(!inputcd(DW)){
      if(gioihan > 35) gioihan--;
   }
}

void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   while(true)
   {
      set_adc_channel(lm35a_channel); 
      delay_us(20);
      tonga += read_adc();
      if(n == 100)
      {
         lm35a = tonga / 2.046 / 100;
         tonga = 0;
         n = 0;
      }else n++;
      
      if(lm35a > gioihan) {
         triac_2_off();
//!         buzzer_on();
      }else if( lm35a < (gioihan-5)) triac_2_on();
//!      else if(lm 35a < gioihan) buzzer_off();
      
      s7seg.led[1] = m7d[lm35a/10%10];
      s7seg.led[0] = m7d[lm35a%10];
      s7seg.led[7] = m7d[gioihan/10%10];
      s7seg.led[6] = m7d[gioihan%10]; 
      s7seg_display();
      check_btn();
   }
}
