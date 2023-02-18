#define BOARD D501
#include <tv_boards.c>

unsigned int8 bdn=0,dem=0;
unsigned int8 phut=0,giay=0,gio=0;
unsigned int8 che_do=0; // che do chay tu 0-6: 0->chinh giay, 2->chinh phut, 4->chinh gio, 6->khong cho chinh
int1 nn;

void check_input(){
   if(!inputcd(UP)){
      if(che_do == 0){
         if(giay == 59) giay = 0;
         else giay++;
         s7seg.led[0] = m7d[giay%10];
         s7seg.led[1] = m7d[giay/10];
      }else if(che_do == 2){
         if(phut == 59) phut = 0;
         else phut++;
         s7seg.led[2] = m7d[phut%10];
         s7seg.led[3] = m7d[phut/10];
      }else if(che_do == 4){
         if(gio == 23) gio = 0;
         else gio++;
         s7seg.led[4] = m7d[gio%10];
         s7seg.led[5] = m7d[gio/10];
      }
   }
   if(!inputcd(DW)){
      if(che_do == 0){
         if(giay == 0) giay = 59;
         else giay--;
         s7seg.led[0] = m7d[giay%10];
         s7seg.led[1] = m7d[giay/10];
      }else if(che_do == 2){
         if(phut == 0) phut = 59;
         else phut--;
         s7seg.led[2] = m7d[phut%10];
         s7seg.led[3] = m7d[phut/10];
      }else if(che_do == 4){
         if(gio == 0) gio = 23;
         else gio--;
         s7seg.led[4] = m7d[gio%10];
         s7seg.led[5] = m7d[gio/10];
      }
   }
   if(!inputcd(MOD)){
      if(che_do == 6) che_do = 0;
      else che_do += 2;
      nn = 0;
   } 
}

void main(){
   system_init();
   
   setup_timer_1(t1_internal|t1_div_by_8); //div_8 de cx
   set_timer1(3036);
   
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   
   while(true){
      if(bdn>=10){
         bdn = bdn - 10;
         if(giay == 59){
            giay = 0;
            if(phut == 59){
               phut = 0;
               if(gio == 23) gio = 0;
               else gio++;
            }
            else phut++;
         }else giay++;
      }
      
      s7seg.led[0] = m7d[giay%10];
      s7seg.led[1] = m7d[giay/10];
      s7seg.led[2] = m7d[phut%10];
      s7seg.led[3] = m7d[phut/10];
      s7seg.led[4] = m7d[gio%10];
      s7seg.led[5] = m7d[gio/10];
      if(nn){
         s7seg.led[che_do]   = 0xff;
         s7seg.led[che_do+1] = 0xff;
      }
      if(che_do < 6)
         if(dem==29){
            dem=0;
            nn = !nn;  
         }
         else dem++;
      
      check_input();
      s7seg_display();
   }
}

#int_timer1
void ngat_timer1(){
   set_timer1(3036);
   bdn++;
}
