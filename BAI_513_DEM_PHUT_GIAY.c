#define BOARD D501
#include <tv_boards.c>

unsigned int8 bdn=0;
unsigned int8 phut=0,giay=0;

void main(){
   system_init();
   
   setup_timer_1(t1_internal|t1_div_by_8);
   set_timer1(3036);
   
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   
   while(true){
      if(bdn>=10){
         bdn = bdn - 10;
         if(giay == 59){
            giay = 0;
            if(phut == 59)phut = 0;
            else phut++;
         }else giay++;
         s7seg.led[0] = m7d[giay%10];
         s7seg.led[1] = m7d[giay/10];
         s7seg.led[2] = m7d[phut%10]-128;
         s7seg.led[3] = m7d[phut/10];
      }
      s7seg_display();
   }
}

#int_timer1
void ngat_timer1(){
   set_timer1(3036);
   bdn++;
}
