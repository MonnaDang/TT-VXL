#include<tv_boards.c> 
#include<tv_lcd.c>
#define solan 100
unsigned int16 tong=0;
unsigned int8 n=0,lm35a;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   set_adc_channel(lm35a_channel); delay_us(20);
   triac_2_off();
   while(true)
   {
      tong += read_adc();
      if(n == solan)
      {
         lm35a = tong / 2.046 / solan;
         tong = 0; n = 0;
      }else n++;
      if(lm35a > 40){
         buzzer_on();
         triac_2_off();
      }else if(lm35a < 35) triac_2_on();
      else if(lm35a < 40) buzzer_off();
      d7seg.led[1] = m7d[lm35a / 10 % 10];
      d7seg.led[0] = m7d[lm35a % 10];
      d7seg_display();
   }
}

