
#include <tv_boards.c>
#include <tv_lcd.c>
#include <tv_key4x4.c>

unsigned int16 y=1,y_temp=1;
unsigned int8 bdn=0,dem=0;


void kt_mtphim(){
   if(key4x4_read() == OK){
      if(key4x4.key <= 9){
        y_temp = key4x4.key;
        lcd_goto(18,1);
        lcd_data(y_temp + 0x30);
      }else if(key4x4.key <= 0x0A){
         if(y_temp > 0){
            y = y_temp;
            buzzer_on();
            enable_interrupts(INT_TIMER1);
            lcd_goto(10,1);
            lcd_data(" ON");
            bdn = 0;
            dem = 0;
         }
//!         delay_ms(y);
//!         buzzer_off();
//!         lcd_goto(10,1);
//!         lcd_data("OFF");
      }
   }
}

void main(){
   system_init();
   lcd_setup();
   
   lcd_goto(2,0);
   lcd_data("DIEU KHIEN BUZZER");   
   lcd_goto(2,1);
   printf(lcd_data,"BUZZER: XXX, TG:1");  
   
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   
   enable_interrupts(GLOBAL);
//!   enable_interrupts(INT_TIMER1);
   
   while(true){
      kt_mtphim();
      if(bdn>=10){
         bdn = bdn - 10;
         dem++;
         if(dem==y){
            buzzer_off();
            lcd_goto(10,1);
            lcd_data("OFF");
            disable_interrupts(INT_TIMER1);
         }
      }
   }
}

#int_timer1
void timer1_isr(){
  bdn++;
  set_timer1(3036);
}
