

#define BOARD D501
#include<tv_boards.c> 
#include <tv_lcd.c>
//!#include <tv_glcd.c>
unsigned int16 adc,tam,tong;
unsigned int8 khoangcach,k_temp=10,n;
void main()
{
   system_init();
   setup_adc(adc_clock_div_32);
   setup_adc_ports(analog_pins|vss_vdd);
   
   lcd_setup();
//!   glcd_setup();
   
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
         
         if(khoangcach < 30){
            lcd_command(lcd_clear_display);
            delay_ms(10);
            lcd_goto(9,1);
            printf(lcd_data,"%02u", khoangcach);
         }else if( khoangcach < 50){
            lcd_write_2x3_num( khoangcach/10,6,1);
            lcd_write_2x3_num( khoangcach/10,9,1);
         }else {
            lcd_write_4x3_num( khoangcach/10,6);
            lcd_write_4x3_num( khoangcach%10,9);
         }
         
      }
   }
}
