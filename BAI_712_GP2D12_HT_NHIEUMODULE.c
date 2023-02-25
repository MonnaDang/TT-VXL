
#define BOARD D501
#include<tv_boards.c> 
#include <tv_lcd.c>
#include <tv_glcd.c>
unsigned int16 adc,tam,tong;
unsigned int8 khoangcach,k_temp=10,n;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   
   lcd_setup();
   glcd_setup();
   
   while(true)
   {
      set_adc_channel(gp2d12_channel); 
      delay_us(20);
      adc = read_adc();
      tam = pow(4277 / adc,1.115);
      if(tam > 80)tam = 80;
      else if(tam < 10)tam = 10;
      tong += tam;
      if(n==100){
         n=0;
         khoangcach = tong/100;
         tong = 0;
      }else n++;
      if(khoangcach != k_temp){
         k_temp = khoangcach;
         d7seg.led[1] = m7d[khoangcach / 10 % 10];
         d7seg.led[0] = m7d[khoangcach % 10];
         d7seg_display();
         
         lcd_goto(0,0);
         lcd_write_2x3_num(khoangcach/10,0,0);
         lcd_write_2x3_num(khoangcach%10,3,0);
         
         glcd_text_setup(0,0,4,1,1);
         printf(glcd_text,"%02u",khoangcach);
         glcd_update();
      }
   }
}
