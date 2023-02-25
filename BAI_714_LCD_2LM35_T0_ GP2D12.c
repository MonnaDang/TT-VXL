
#define BOARD D501
#include<tv_boards.c> 
#include<tv_lcd.c>
#define solan 100
unsigned int16 tonga=0,tongb=0;
unsigned int8 n=0,lm35a,lm35b,T0=0,T0_temp = 99;
unsigned int8 k;
unsigned int16 adc,tam,tong;
unsigned int8 khoangcach,k_temp=10;
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
//!      // Ðo LM35B
      set_adc_channel(lm35b_channel);
      delay_us(20);
      tongb += read_adc();
      
      // Do khoang cach
      set_adc_channel(gp2d12_channel); 
      delay_us(20);
      adc = read_adc();
      tam = pow(4277 / adc,1.115);
      if(tam > 80)tam = 80;
      else if(tam < 10)tam = 10;
      tong += tam;
  
      T0 = get_timer0();
      if(T0 > 99){
         T0 = T0 - 99;
         set_timer0(T0);
      }
      if(T0 != T0_temp){
         T0_temp = T0;
         lcd_goto(0,1);
         printf(lcd_data,"DEM SAN PHAM: %02u",T0);
      }
  
      if(n == solan)
      {
         lm35a = tonga / 2.046 / solan;
         lm35b = tongb / 2.046 / solan;
         tonga = 0; tongb = 0; n = 0;
         lcd_goto(0,0);
         printf(lcd_data,"LM35A: %02u LM35B: %02u",lm35a,lm35b);
      }else n++;
      
      
      if(k==100){
         k=0;
         khoangcach = tong/100;
         tong = 0;
      }else k++;
      
      if(khoangcach != k_temp){
         k_temp = khoangcach;
         lcd_goto(0,2);
         printf(lcd_data,"KHOANG CACH %02u", khoangcach);
      }
   }
}
