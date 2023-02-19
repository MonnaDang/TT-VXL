
#include <tv_boards.c>
#include <tv_glcd.c>
#include <tv_lcd.c>

unsigned int8 bdn=0,giay=0,phut=0,gio=0;
unsigned int8 T0=0,T0_temp=99;
unsigned int8 i=0,j=0,mode=0;
unsigned int16 k=0;

void check_counter0(){
   T0 = get_timer0();
   if(T0 > 99){
      T0 = T0 - 99;
      set_timer0(T0);
   }
   
   if(T0 != T0_temp){
      T0_temp = T0;
      
      d7seg.led[0] = m7d[T0%10];
      d7seg.led[1] = m7d[T0/10];
      d7seg_display();
      
      lcd_goto(0,0);
      printf(lcd_data,"COUNTER0: %02u",T0);
      
      glcd_text_setup(0,0,2,1,1);
      printf(glcd_text,"COUNTER0: %02u",T0);
      glcd_update();
   }
}

void check_timer1(){
   if(bdn>=10){
      bdn = bdn - 10;
      if(giay == 59){
         giay = 0;
         if(phut == 59){
            phut=0;
            if(gio == 23)gio=0;
            else gio++;
         }else phut++;
      }else giay++;
      s7seg.led[0] = m7d[giay%10];
      s7seg.led[1] = m7d[giay/10];
      s7seg.led[2] = m7d[phut%10];
      s7seg.led[3] = m7d[phut/10];
      s7seg.led[4] = m7d[gio%10];
      s7seg.led[5] = m7d[gio/10];
   }
}

void my_delay(){
   led32_display();
   for(k=0;k<50;k++){
      check_counter0();
      check_timer1();
      s7seg_display();
   }
}

void SangTatDan_PST(){
   if(i<32) led32.ledx32 = (int32)(led32.ledx32<<1)|(int32)1;
   else led32.ledx32 = led32.ledx32<<1;
   if(i==63){
      i=0;
      mode = 1;
   }
   else i++;
   my_delay();
}

void SangTatDan_N(){
   if(i<16){
      led32.ledx16[0] = (int16)(led32.ledx16[0]<<1)|(int16)1;
      led32.ledx16[1] = (int16)(led32.ledx16[1]>>1)|0x8000;
   }else{
      led32.ledx16[0] = (int16)led32.ledx16[0]<<1;
      led32.ledx16[1] = (int16)led32.ledx16[1]>>1;
   }
   if(i==31){
      i=0;
      mode=2;
   }
   else i++;
   my_delay();
}

void  SangDon_PST(){
   if(i==32) {
      i = 0;
      mode = 0;
   }
   else{
      if(j==(32-i)){
         j=0;
         i++;
      }else{
         led32.ledx32 = (~(0xffffffff>>i))|((int32)1<<j);
         j++;
         my_delay();
      }
   }
}

void main(){
   system_init();
   lcd_setup();
   glcd_setup();
   
   setup_timer_0(T0_EXT_H_TO_L| T0_DIV_1);
   set_timer0(0);
   
   setup_timer_1(T1_INTERNAL| T1_DIV_BY_8);
   set_timer1(3036);
   
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_TIMER1);
   
   led32.ledx32=0;
   
   while(true){
      if(mode == 0){
         SangTatDan_PST();
      }else if(mode == 1){
         SangTatDan_N();
      }else if(mode == 2){
         SangDon_PST();
      }
   }
}

#int_timer1
void timer1_isr(){
   bdn++;
   set_timer1(3036);
}
