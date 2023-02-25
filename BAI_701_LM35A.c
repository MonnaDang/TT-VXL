
#include<tv_boards.c> 
#include<tv_lcd.c>
unsigned int16 lm35a;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   set_adc_channel(lm35a_channel); delay_us(20);
   while(true)
   {
      lm35a = read_adc() / 2.046;
      d7seg.led[1] = m7d[lm35a / 10 % 10];
      d7seg.led[0] = m7d[lm35a % 10];
      d7seg_display();
   }
}
