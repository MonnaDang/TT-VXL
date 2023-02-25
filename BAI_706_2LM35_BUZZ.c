
#include<tv_boards.c> 
#include<tv_lcd.c>
#define solan 100
unsigned int16 tonga=0,tongb=0;
unsigned int8 n=0,lm35a,lm35b;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   while(true)
   {
      // Ðo LM35A
      set_adc_channel(lm35a_channel); delay_us(20);
      tonga += read_adc();
      // Ðo LM35B
      set_adc_channel(lm35b_channel); delay_us(20);
      tongb += read_adc();
  
      if(n == solan)
      {
         lm35a = tonga / 2.046 / solan;
         lm35b = tongb / 2.046 / solan;
         tonga = 0; tongb = 0; n = 0;
      }else n++;
      
      if( (lm35a > 40) || (lm35b > 40) ){
         triac_2_off();
         buzzer_on();
      }else if((lm35a < 35) && (lm35b < 35)) triac_2_on();
      else if((lm35a < 40) && (lm35b < 40)) buzzer_off();
      
      d7seg.led[1] = m7d[lm35a / 10 % 10];
      d7seg.led[0] = m7d[lm35a % 10];
      d7seg.led[3] = m7d[lm35b / 10 % 10];
      d7seg.led[2] = m7d[lm35b % 10] - 128; 
      d7seg_display();
   }
}
