#define BOARD D501
#include<tv_boards.c> 
unsigned int16 distance;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   while(true)
   {
      set_adc_channel(gp2d12_channel); delay_us(20);
      distance = read_adc();
      distance = pow(4277 / distance,1.115);
      if(distance > 80)distance = 80;
      else if(distance < 10)distance = 10;
      d7seg.led[1] = m7d[distance / 10 % 10];
      d7seg.led[0] = m7d[distance % 10];
      d7seg_display();
   }
}
