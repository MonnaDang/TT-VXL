#define BOARD D501
#include<tv_boards.c> 
#include<tv_lcd.c>
#define solan 100
unsigned int16 tonga=0,tongb=0;
unsigned int8 n=0,lm35a,lm35b,T0=0,T0_temp = 99;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   
   lcd_setup();
   while(true)
   {
      // Ðo LM35A
      set_adc_channel(lm35a_channel); 
      delay_us(20);
      tonga += read_adc();
      // Ðo LM35B
      set_adc_channel(lm35b_channel);
      delay_us(20);
      tongb += read_adc();
  
      T0 = get_timer0();
      if(T0 > 99){
         T0 = T0 - 99;
         set_timer0(T0);
      }
      if(T0 != T0_temp){
         T0_temp = T0;
         lcd_goto(0,2);
         printf(lcd_data,"DEM SAN PHAM: %02u",T0);
      }
  
      if(n == solan)
      {
         lm35a = tonga / 2.046 / solan;
         lm35b = tongb / 2.046 / solan;
         tonga = 0; tongb = 0; n = 0;
         lcd_goto(0,0);
         printf(lcd_data,"NHIET DO LM35A: %02u",lm35a);
         lcd_goto(0,1);
         printf(lcd_data,"NHIET DO LM35A: %02u",lm35b);
      }else n++;
      
      if( (lm35a > 40) || (lm35b > 40) ){
         triac_2_off();
//!         buzzer_on();
      }else if((lm35a < 35) && (lm35b < 35)) triac_2_on();
//!      else if((lm35a < 40) && (lm35b < 40)) buzzer_off();
   }
}
