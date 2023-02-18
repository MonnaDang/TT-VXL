
#define BOARD D501
#include <tv_boards.c>
#include <tv_lcd.c>

unsigned int8 bdn,dem;
unsigned int8 phut=0,giay=0;

void main(){
   system_init();
   setup_timer_1(t1_internal| T1_DIV_BY_8);
   set_timer1(3036);
   
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   
   lcd_setup();
   
   while(true){
      if(bdn>=10){
         bdn = bdn - 10;
         if(giay == 59){
            giay = 0;
            if(phut == 59){
               phut = 0;
            }else phut++;
         }else giay++;
         lcd_goto(7,0);
         printf(lcd_data,"%2u %2u",phut,giay);
      }
   }
}

#int_timer1
void ngat_timer1(){
   bdn ++;
   set_timer1(3036);
}
